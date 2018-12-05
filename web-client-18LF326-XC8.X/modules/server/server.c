#include "../../config.h"
#include "server-primary.h"
#include "server.h"
#include "../transmitter/transmitter.h"
#include "../receiver/receiver.h"
//
static server_SelfData server_self;

uint8_t server_task(void){
    
    uint8_t didSomeWork = false;    
    
    while(__hasPendingEv()){
        // Event Send Root
        if( __isRaisedEv(evSendRes) ){
            if( dispatchevSendRes() ) {
                didSomeWork = true;
                __clearEv(evSendRes);
            }
        } else if( __isRaisedEv(evMsgOk) ){
            if( dispatchEvMsgOk() ) {
                didSomeWork = true;
                __clearEv(evMsgOk);
            }
        } else if( __isRaisedEv(evSendNotFound) ) {
            if( dispatchEvSendNotFound() ){
               didSomeWork = true;
                __clearEv(evSendNotFound); 
            }
        }
        
    }
    
    return didSomeWork;
    
}

/************************** PUBLIC METHODS **************************/
void server_raiseEventSendData(server_Routes route){
    
    switch (route){
        case server_routeRoot:{
            __raiseEv(evSendRes);
            __setRoute(route);
            break;
        }
    }
}

void server_raiseEventNotFound(void){
    __raiseEv(evSendNotFound);
}

void server_raiseEventMsgOk(void){
    __raiseEv(evMsgOk);
}

/**************************EVENT DISPATCHERS **************************/

static uint8_t dispatchEvSendNotFound(void){
    return true;
}


static uint8_t dispatchEvMsgOk(void){
    
    static uint8_t done = 0;
    
    switch (__state){
        //=== MSG "OK" - STATE
        case __stSendingResHederStatusLineDataSize : {
            switch (__route){
                case server_routeRoot:{
                    if( transmitter_send((uint8_t*)HTTP_HEADER_OK_STATUS_LINE_OK, sizeof(HTTP_HEADER_OK_STATUS_LINE_OK) - 1 ) ) {
                        enterSt_sendingResHederStatusLineOk();
                        return true;
                    }                    
                    break;
                } default:{
                    return false;
                }
                
            }

            break;
        } 
        //=== MSG OK - STATE
        case __stSendingResHederStatusLineOk:{
            switch (__route){
                case server_routeRoot:{
                    if( transmitter_send((uint8_t*)HTTP_BODY_SEPARATOR_SIZE, sizeof(HTTP_BODY_SEPARATOR_SIZE) - 1 ) ) {
                        enterSt_sendingBodySeparatorSize();
                        return true;
                    }
                    break;
                    
                } default:{
                    
                }
                
            }
        }
        //=== MSG OK - STATE
        case __stSendingBodySeparatorSize:{
            switch (__route){
                case server_routeRoot:{
                    if( transmitter_send((uint8_t*)HTTP_BODY_SEPARATOR, sizeof(HTTP_BODY_SEPARATOR) - 1 ) ){
                        enterSt_sendingBodySeparator();
                        return true;
                    }
                    
                    break;
                } default:{}
            }
            break;
        }
        //=== MSG OK - STATE
        case __stSendingBodySeparator:{
            enterSt_sendingBody();
        }
        case __stSendingBody: {
            switch( doSt_sendingBody() ){
                case __serverCode_didNothing :{ //Wait transmitter 
                    return false;
                    break;
                } case __serverCode_didSomeWork:{ //Wait new OK-MSG event 
                    return true;
                    break;
                } case __serverCode_done :{ //Wait new OK-MSG event, but change state
                    enterSt_closinTcpConnection();
                    return false; //Force doing ClosingTcpConnection at least once
                    break;
                } default:{
                    return false;
                }
            }
            break;
        }
            
        case __stClosingTcpConnection:{
            
            if(done){
                done = 0;
                exitSt_closingTcpConnection();
                enterSt_idle();
                return true;
            } else {
                if( doSt_closinTcpConnection() ) {
                    done = 1;
                    return true;
                } else {
                    return false;
                }
            }
            
            break;
        }
        //=== MSG OK - STATE
        default:{

        }
    }
    
    return false;
} 



static uint8_t dispatchevSendRes(void){
    switch(__state){
        case __stIdle:{
            switch (__route){
                case server_routeRoot:{
                    if( transmitter_send((uint8_t*)HTTP_HEADER_OK_SIZE, sizeof(HTTP_HEADER_OK_SIZE) - 1 ) ) {
                        enterSt_sendingResHederStatusLineDataSize();
                        return true;
                    }
                    break;
                }
            }
            break;
        }
        default:{
            
        }
    }
    return false;
}

/************************** EVENT HANDLERS **************************/

/************************** OTHERS **************************/
static server_Code sendBoydRoot(void){
    char txBuff[] = "AT+CIPSEND=0,2048\r\n";
    typedef enum {
        sendSize,
        sendBodyFr,
    }SendingState;
    

    
    typedef struct {
     SendingState state; 
     char * start;
     uint16_t strSize;
     uint16_t remain;
     uint8_t once;
    }Self;
    
    static Self self = {.once = 1};
    
    if(self.once){
        self.state = sendSize;
        self.start = (char*)HTTP_BODY_ROOT;
        self.strSize = sizeof(HTTP_BODY_ROOT) - 1; // exclude NULL character
        self.remain = self.strSize;
        self.once = 0;
    }
    
    if(self.remain > 0){
        switch (self.state) {
            //== STATE  :  send AT+CIPSEND=???
            case sendSize:{
                if( self.remain >=  PACKAGE_MAX_SIZE){
                    if( transmitter_send((uint8_t*)txBuff, sizeof(txBuff) - 1) ){
                        self.state = sendBodyFr;
                        return __serverCode_didSomeWork;                       
                    } else {
                        return __serverCode_didNothing;
                    }
                } else { //remain < PACKAGE_MAX_SIZE. Next Body chunk is the last
                    sprintf( (char*)txBuff, "AT+CIPSEND=0,%u\r\n", self.remain );
                        if(transmitter_send((uint8_t*)txBuff, strlen(txBuff)) ){
                            self.state = sendBodyFr;
                            return __serverCode_didSomeWork;
                        } else {
                            return __serverCode_didNothing;
                        }
                }
                break;
            } case sendBodyFr:{
                if(self.remain >= PACKAGE_MAX_SIZE){
                    if(transmitter_send((uint8_t*)self.start, PACKAGE_MAX_SIZE) ){
                        self.start += PACKAGE_MAX_SIZE;
                        self.remain -= PACKAGE_MAX_SIZE;
                        self.state = sendSize;
                        return __serverCode_didSomeWork;
                    } else { 
                        return __serverCode_didNothing;
                    }
                } else { //Last Body chunk self.remain < PACKAGE_MAX_SIZE
                    if(transmitter_send((uint8_t*)self.start, self.remain) ){
                        
                        self.remain = 0;
                        return __serverCode_didSomeWork;    
                    } else {
                        return __serverCode_didNothing;
                    }
                }
                 
                break;
            } default:{
                 return __serverCode_didNothing;
            }
            
        } 
    }else { //Ramain nothing 
        self.once = 1; 
        return __serverCode_done;
        
    }
    
    
    
    
}

/************************** STATE TRANSITIONS **************************/

/****** IDLE ******/

static void enterSt_idle(void){
    __setSt(__stIdle);
}

/****** STATUS LINE ******/
static void enterSt_sendingResHederStatusLineDataSize(void){
    __setSt(__stSendingResHederStatusLineDataSize);
}


static void enterSt_sendingResHederStatusLineOk(void){
    __setSt(__stSendingResHederStatusLineOk);
//    server_raiseEventSendData(__route);
}

/****** BODY SEPARATOR ******/
static void enterSt_sendingBodySeparatorSize(void){
    __setSt(__stSendingBodySeparatorSize);
}

static void enterSt_sendingBodySeparator(void){
    __setSt(__stSendingBodySeparator);
    
}

static void enterSt_sendingBody(void){
    __setSt(__stSendingBody);
}

static server_Code doSt_sendingBody(void){
    switch (__route){
        case server_routeRoot:{
            return sendBoydRoot();
            break;    
        } default:{
            return __serverCode_didNothing;
        }
    }    
} 

static void enterSt_closinTcpConnection(void){
    __setSt(__stClosingTcpConnection);

}

static uint8_t doSt_closinTcpConnection(void){
    if(transmitter_send( (uint8_t*)CLOSE_TCP_CONNECTION, sizeof(CLOSE_TCP_CONNECTION)- 1) ){
        return true;
    } else {
        return false;
    } 
}


static void exitSt_closingTcpConnection(void){
    receiver_resetFrBuff();
}