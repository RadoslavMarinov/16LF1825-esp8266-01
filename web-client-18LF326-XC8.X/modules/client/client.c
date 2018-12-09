
#include "../../config.h"
#include "client-primary.h"
#include "client.h"
#include "../transmitter/transmitter.h"

static client_Self client_self;

uint8_t client_task(void){

    if(__isRaisedEv(evDo)){
    
        if(dispatchEv_evDo()){
            __clearEv(evDo);
            return true;
        }
    }
    
    if(__isRaisedEv(evMsgOk)){
        if( dispatchEv_evMsgOk() ){
            __clearEv(evMsgOk);
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


uint8_t client_raiseEvStart(void){
    if(__inSt(stIdle) ){
       __raiseEv(evStart); 
       return true;
    } else {
        return false;
    }
}

uint8_t client_raiseEv_do(void){
#ifdef UNDER_TEST 
    if(__isRaisedEv(evDo)){
        __raiseErr(erEvDoRaiseOvrfl);
        CONFIG_stopHere();
    }
#endif
    __raiseEv(evDo);
    return true;
}

uint8_t client_raiseEventMsgOk(void){
#ifdef UNDER_TEST 
    if(__isRaisedEv(evMsgOk)){
        __raiseErr(erEvevMsgOkRaiseOvrfl);
        CONFIG_stopHere();
    }
#endif
    __raiseEv(evMsgOk);
    return true;
    
}

/*************************** EVENT DISPATCHERS ***************************/

static uint8_t dispatchEv_evMsgOk(void){
    switch(__state){
        case stUpdateServer:{
            switch(updateServer()){
                case code_didSomeWork:{
                    return true;
                }
                case code_done:{
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
            enterSt_updateServer();
            client_raiseEv_do();
            break;
        }
        default:{}
    }
    return 1;
}

static uint8_t dispatchEv_evDo(void){
    switch(__state){
        case stUpdateServer:{
            switch(updateServer()){
                case code_didSomeWork:{
                    return true;
                }
                case code_done:{
                    return true;
                } default:{
                    
                }
            }
            break;
        } 
        default:{
            
        }
    }
    return 1;
}

static client_Code updateServer(void){
    char size[20];
    
    static struct{
        enum{
          stSendSize,
          stSendPkg,
        }state;
        uint16_t size;
        unsigned int once:1;
    }self = {.once = 1};
    
    if(self.once){
        strcpy(__txBuff, COMMAND_POST_SERVER_UPDATE_HEADER);
        self.size = strlen(__txBuff);
        
        composePostUpdateBody( ((char*)__txBuff) + self.size);
        self.size = strlen(__txBuff) - 1 ;
    }
    
    switch(self.state){
        case stSendSize:{
            
            
            
            strcpy(size, "AT+CIPSEND=");
            sprintf(size + 11, "%u", self.size);
//            strcat(__txBuff, size);
            strcat(size, "\r\n");
            
            
            
            if(transmitter_send((uint8_t*)size, strlen(size))){
                self.state = stSendPkg;
                return code_didSomeWork;
            }
            break;
        }
        case stSendPkg:{
            if(transmitter_send((uint8_t*)__txBuff, self.size)){
                self.state = stSendPkg;
                return code_didSomeWork;
            }
        }
        default:{
            
        }
    }
    
    return code_didNothing;
}

/*************************** STATE TRANZITION ***************************/
static void enterSt_updateServer(void){
    __setSt(stUpdateServer);
}

/*************************** OTHERS ***************************/
static uint8_t composePostUpdateBody(char* startAddr){
    char * cur = startAddr;
    // DEVICE ID
    strcpy(cur, "{\"id\":\""DEVICE_ID"\"");
    //
    strcat(cur, ",");
    // SWITCH 1 STATE
    strcat(cur, "\"rsw1s\":");
    strcat(cur, GET_SW1_VALUE() ? "\"on\"": "\"off\"");
    //
    strcat(cur, ",");
    // SWITCH 1 STATE
    strcat(cur, "\"rsw2s\":");
    strcat(cur, GET_SW2_VALUE() ? "\"on\"": "\"off\"");
    //
    strcat(cur, "}\r\n\r\n");
    return 1;
}

