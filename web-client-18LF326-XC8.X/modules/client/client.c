
#include "../../config.h"
#include "client-primary.h"
#include "client.h"
#include "../timer/timer.h"
#include "../transmitter/transmitter.h"

static client_Self client_self;

uint8_t client_task(void){

    if(__isRaisedEv(evMsgOk)){
        if( dispatchEv_evMsgOk() ){
            __clearEv(evMsgOk);
            return true;
        }
    }
    
    if(__isRaisedEv(evUpdateServer)){
        if( dispatchEv_updateServer() ){
            __clearEv(evUpdateServer);
            return true;
        }
    }
    
    if(__isRaisedEv(evError)){
        if( dispatchEv_error() ){
            __clearEv(evError);
            return true;
        }
    }
    
    if(__isRaisedEv(evAck)){
    
        if(dispatchEv_evAck()){
            __clearEv(evAck);
            return true;
        }
    }
    
    if(__isRaisedEv(evStart)){
    
        if(dispatchEv_evStart()){
            __clearEv(evStart);
            return true;
        }
    }
    return false;
}

/****************************** INITS ******************************/

void client_init(client_OnError onErr){
    __clearAllEvs();
    __setSt(stIdle);
    __setOnErr(__onErrDummy); // in case param "onErr" is NULL - fucking compiler trick
    __setOnErr(onErr);
}


/****************************** EVENT RAISERS ******************************/
uint8_t client_raiseEventAck(void){
    if(__inSt(stIdle)){
        __raiseEv(evAck);
        return true;
    } else {
        #ifdef UNDER_TEST
        CONF_raiseNvErrBit(conf_nvErr_client_evUpdServerInWrongState);
        #endif
        return false;
    }  
}

 uint8_t client_raiseEvenUpdateServer(void){
    if(__inSt(stIdle)){
        __raiseEv(evUpdateServer);
        
        return true;
    } else {
        #ifdef UNDER_TEST
        __raiseErr(erEvevUpdateServerInWrongState);
        CONF_raiseNvErrBit(conf_nvErr_client_evUpdServStErr);
        #endif
        return false;
    }
}

uint8_t client_raiseEventError(void){
    __raiseEv(evError);
    return 1;
}
 
uint8_t client_raiseEvStart(void){
    if(__inSt(stIdle) ){
       __raiseEv(evStart); 
       return true;
    } else {
        #ifdef UNDER_TEST
        CONF_raiseNvErrBit(conf_nvErr_client_evStartRaisedInWrongState);
        #endif
        return false;
    }
}


uint8_t client_raiseEventMsgOk(void){
#ifdef UNDER_TEST 
    if(__isRaisedEv(evMsgOk)){
       CONF_raiseNvErrBit(conf_nvErr_client_evMsgOkRaiseOvrfl);
    }
#endif
    __raiseEv(evMsgOk);
    return true;
    
}

/*************************** EVENT DISPATCHERS ***************************/
static uint8_t dispatchEv_evAck(void){
    switch (__state){
        case stIdle:{
            LED_GREEN_ON();
            LED_RED_OFF();
            return 1;
        }
        default :{
            CONF_raiseNvErrBit(conf_nvErr_client_evAckRaisedInNonIdle);
            #ifdef UNDER_TEST
//            CONFIG_stopHere();
            #endif
        }
    }
    return 0;
}


static uint8_t dispatchEv_error(void){
    switch (__state){
        case stClosingTcpConnection:{
            enterSt_connectServer();
            return true;
            break;
        } 
        case stConnectServer:{
            timer_stop(__timerGetHook(client_tmrServerAliveTimeout));
            clearTimerHooks();
            __callOnErr(NULL);
            return true;
            //            SYSTEM_softReset();
        }
        default:{
            #ifdef UNDER_TEST
            __raiseErr(erEvErrorAtWrongState);
            CONF_raiseNvErrBit(conf_nvErr_client_clErrInUndefinedState);
//            CONFIG_stopHere();
            return false;
            #endif
        }
    }
    
}

static uint8_t dispatchEv_updateServer(void){
    switch (__state){
        case stIdle:{
            return handleEv_updateServer();
            break;
        } default:{

        }
    }
    return false;
}

static uint8_t dispatchEv_evMsgOk(void){
    switch(__state){
        case stClosingTcpConnection:{
            enterSt_connectServer();
            break;
        }
        case stConnectServer:{
            enterSt_updateServer();
            break;
        }
        case stUpdateServer:{
            switch(updateServer()){
                case code_didSomeWork:{
                    return true;
                }
                case code_done:{
                    enterSt_idle();
                    return true;
                } case code_didNothing:{
                    return false;
                }
            }
        }
        default:{
            #ifdef UNDER_TEST 
            __raiseErr(erEvevMsgOkRaisedInWrongState);
            CONFIG_stopHere();
            #endif
        }
    }
    return true;
}

static uint8_t dispatchEv_evStart(void){
    switch(__state){
        case stIdle:{
//            enterSt_connectServer();
            client_raiseEvenUpdateServer();
            return 1;
            break;
        }
        default:{
            #ifdef UNDER_TEST
            __raiseErr(erEventStartRaisedInWrongState);
            CONFIG_stopHere();
            #endif
        }
    }
    return 0;
}


/****************************** EVENT HANDLERS ****************************** */
static uint8_t handleEv_updateServer(void){
    timer_Hook hook;
    if( __timerEnabled(client_tmrServerAliveTimeout) ){
        timer_reset(__timerGetHook(client_tmrServerAliveTimeout));
    } else {
        hook = timer_start(timer_getTicksFromSeconds(SERVER_UPD_TIMEOUT_S), onServerAliveTimeout);
        __timerEnable(client_tmrServerAliveTimeout, hook);
    }
    
    if(transmitter_send((uint8_t*)COMMAND_CLOSE_TCP, sizeof(COMMAND_CLOSE_TCP))){
        enterSt_closingTcpConnection();
        return true;
    }
    return false;
}

/****************************** OTHERS ****************************** */
static client_Code updateServer(void){
    char size[20];
    uint16_t bodySize, headerSize;
    
    static struct{
        enum{
            stIdle,
            stSendSize,
            stSendPkg,
        }state;
        uint16_t size;
        unsigned int once:1;
    }self = {.once = 1};
    
    if(self.once){
        strcpy(__txBuff, COMMAND_POST_SERVER_UPDATE_ST_LINE);
        
        self.size = strlen(__txBuff);
        
        bodySize = composePostUpdateBody( ((char*)__bodyBuff));
        
        headerSize = composePostUpdateHeader(__txBuff, bodySize);
        
        strcat(__txBuff, __bodyBuff);
        
        self.size =  headerSize + bodySize;
        
        self.once = 0;
    }
    
    switch(self.state){
        case stIdle:{
            
            strcpy(size, "AT+CIPSEND=");
            sprintf(size + 11, "%u", self.size);
//            strcat(__txBuff, size);
            strcat(size, "\r\n");
            
            
            
            if(transmitter_send((uint8_t*)size, strlen(size))){
                self.state = stSendSize;
                return code_didSomeWork;
            }
            break;
        }
        case stSendSize:{
            if(transmitter_send((uint8_t*)__txBuff, self.size)){
                self.state = stSendPkg;
                return code_didSomeWork;
            }
        }case stSendPkg:{
            self.state = stIdle;
            self.once = 1;
            return code_done;
        }
        default:{
            
        }
    }
    
    return code_didNothing;
}

/*************************** STATE TRANZITION ***************************/

static uint8_t enterSt_connectServer(void){
    if(transmitter_send((uint8_t*)COMMAND_CONNECT_SERVER, sizeof(COMMAND_CONNECT_SERVER) - 1 ) ){
        __setSt(stConnectServer);
        return true;
    } else {
        #ifdef UNDER_TEST
        __raiseErr(erTrBusy);
        CONFIG_stopHere();
        #endif
        return false;
    }
    
}

static void enterSt_closingTcpConnection(void){
    __setSt(stClosingTcpConnection);
}
static uint8_t enterSt_updateServer(void){
    __setSt(stUpdateServer);
    switch(updateServer()){
        case code_didNothing:{
            return false;
        }
        case code_didSomeWork:{
            return true;
        }
        case code_done:{
            enterSt_idle();
            return true;
        } default:{

        }
    }
}
//
//static void exitSt_updateServer(void){
//    
//}

static void enterSt_idle(void){
    __clearAllEvs();
    __setSt(stIdle);
}

/*************************** OTHERS ***************************/


static uint16_t composePostUpdateBody(char* startAddr){
    char * cur = startAddr;
    // DEVICE ID
    strcpy(cur, "{\"id\":\""DEVICE_ID"\"");
    //
    strcat(cur, ",");
    // endpoints
    strcat(cur, "\"endpoints\":");
    //SW1
    strcat(cur, "[{\"bs1\":{\"state\":");
    strcat(cur, SWITCH1_GET_VALUE() ? "1": "0");
    strcat(cur, "}},");
    //SW2
    strcat(cur, "{\"bs2\":{\"state\":");
    // SWITCH 1 STATE
    strcat(cur, SWITCH2_GET_VALUE() ? "1": "0");
    strcat(cur, "}}]}");
    //
    strcat(cur, "\r\n\r\n");
    return strlen(cur);
}

static uint16_t composePostUpdateHeader(char * stAddr, uint16_t bodySize){
    char bodySizeStr[6];
    strcpy(stAddr, COMMAND_POST_SERVER_UPDATE_ST_LINE);
    // Content Type
    strcat(stAddr, "Content-Type: application/json\r\n");
    // Content Length
    sprintf(bodySizeStr, "%u", bodySize);
    strcat(stAddr, "Content-Length: ");
    strcat(stAddr, bodySizeStr);
    
    
    strcat(stAddr, "\r\n\r\n");
    
    return strlen(stAddr);
}

static void clearTimerHooks(void){
    uint8_t i;
    for(i=0; i < client_tmrsNumber; i++){
        __timerDisable(i);
    }
}

// == CALBACKS ====================================


static void onServerAliveTimeout(void){
    __timerDisable(client_tmrServerAliveTimeout);
//    config_dummyFunc();
    if(__onError != NULL ){
        __onError("Server Not Available!");
    } else {
        CONF_raiseNvErrBit(conf_nvErr_client_OnErrCallBackNull);
    }
    LED_GREEN_OFF();
    //    communicator_init(false, communicator_espModeStation);
//    esp_reset(timer_getTicksFromMS(ESP_RESET_TIME_MS), receiver_start())
}

//static void  onServerAckTimeout(void){
//#ifdef UNDER_TEST
////    CONFIG_stopHere();
//#endif
//    CONF_raiseNvErrBit(conf_nvErrClent_AckTimeOut);
//    __raiseErr(clientAckTimeout);
//    SYSTEM_softReset();
//}
//
//static void  onServerUpdTimeout(void){
//#ifdef UNDER_TEST
//    __raiseErr(clientUpdTimeout);
////    CONFIG_stopHere();
//#endif
//    CONF_raiseNvErrBit(conf_nvErrClent_UpdTimeOut);
//    SYSTEM_softReset();
//}


