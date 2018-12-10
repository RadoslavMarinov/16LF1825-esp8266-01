
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
    uint16_t bodySize, headerSize;
    
    static struct{
        enum{
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


static uint16_t composePostUpdateBody(char* startAddr){
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