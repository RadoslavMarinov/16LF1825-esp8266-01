#include "../../config.h"
#include "../eeprom/eeprom.h"
#include "communicator-primary.h"
#include "communicator.h"
#include "../receiver/receiver.h"
#include "../transmitter/transmitter.h"
#include "../parser/parser.h"
#include "../parser/json-parser/json-parser.h"

Self comm_self;


/************************************************************************
 * GLOBAL METHODS
 ***********************************************************************/
uint8_t communicator_task(void){
    uint8_t didWork = false;
    if( __isPendingEv() ) {
        if( __isRaisedEv(evReset) ){
            didWork = dispatchEvReset();
        }
        else if(__isRaisedEv(evWaitReceiver)){
            if(dispatchEventWaitReceiver()){
                __clearEv(evWaitReceiver);
                didWork = true;
            }
            
        }
    }
    return didWork;
}


void communicator_init(uint8_t start, communicator_EspMode espMode){
    __setEspMode(espMode);
    communicator_initSelf();
    receiver_init(handleMessage, false);
    transmitter_init(NULL);
    
//    parser_init(handleMessage);
    if(start){
        __raiseEv(evReset);
    }
}





/************************************************************************
 * STATIC METHODS
 ***********************************************************************/
static void communicator_initSelf(void){
    __clearAllEvents();
    __setState(stOff);

}



/************************************************************************
 * STATIC EVENT DISPATCHERS
 ***********************************************************************/
static uint8_t dispatchEvReset(void) {
    return handleEvReset();
}

static uint8_t dispatchEventWaitReceiver(void) {
    switch (__state) {
        case stUpdateServer:{
            return enterState_updateServer();
        }
        default:{
        #ifdef UNDER_TEST
        __raiseErr(errEvWaitReceiverRaisedInWrongState);
        CONFIG_stopHere();
        #endif
        }
    }
}

/************************************************************************
 * STATIC EVENT HANDLERS
 ***********************************************************************/
static uint8_t handleEvReset(void){
    communicator_init(false, __espMode);
    transmitter_send((uint8_t*)COMMAND_RESET, sizeof(COMMAND_RESET) - 1);
    __setState(stReset);
    return true;
}

/************************************************************************
 * STATIC STATE TRANSITION
 ***********************************************************************/
static void enterSt_turnOffEcho(void){
    __setState(stTurnOffEcho);
    transmitter_send((uint8_t*)COMMAND_TURN_OFF_ECHO, sizeof(COMMAND_TURN_OFF_ECHO) - 1);
//    WAIT RESPONSE "OK"
}

static void enterSt_setWifiMode(communicator_EspMode espMode){
    __setState(stSetWifiMode);
    
    switch(espMode){
        case communicator_espModeStation:{
            if(false == __trSend(COMMAND_SET_MODE_STATION, sizeof(COMMAND_SET_MODE_STATION) - 1 )){
                #ifdef UNDER_TEST
                __raiseErr(errTrBusy);
                CONFIG_stopHere();
                #endif
            }
            break;
        }
        case communicator_espModeAccessPoint:{
            if(false == __trSend(COMMAND_SET_MODE_ACCESS_POINT, sizeof(COMMAND_SET_MODE_ACCESS_POINT) - 1 )){
                #ifdef UNDER_TEST
                __raiseErr(errTrBusy);
                CONFIG_stopHere();
                #endif
            }
            break;
        }
        case communicator_espModeDual: {
            break;
        }
        default:{
            
        }
    }
}

static void enterSt_connectToAp(void){
    
    __setState(stJoinAp);
    strcpy( (char*)__txBuff, "AT+CWJAP=\"");
    eeprom_readWifiSsid( &__txBuff[strlen(__txBuff)] );
    strcat( (char*)__txBuff, "\",\"");
    eeprom_readWifiPwd( &__txBuff[strlen(__txBuff)] );
    strcat( (char*)__txBuff, "\"\r\n");
    if( false == __trSend(__txBuff, strlen(__txBuff) ) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
}

static void enterSt_setAp(void){
       __setState(stSetAp);
    if( false == __trSend(COMMAND_SET_AP, sizeof(COMMAND_SET_AP) - 1) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    } 
}

static void enterState_connectServer(){
    __setState(stConnectServer);
    if( false == __trSend(COMMAND_CONNECT_SERVER, sizeof(COMMAND_CONNECT_SERVER) - 1 ) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
}

static void enterState_setMsgLength(void){
    uint16_t length;
    char msgSizeCmd[20];
    __setState(stSeMsgLength);
    
    strcpy(msgSizeCmd, "AT+CIPSEND=");
    sprintf(&msgSizeCmd[11], "%d\r\n", sizeof(COMMAND_POST_SERVER_UPDATE) - 1);
    if( false == __trSend(msgSizeCmd, strlen(msgSizeCmd)) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
}

static uint8_t enterState_updateServer(void){
    
    __setState(stUpdateServer);
    
    if(receiver_getCircBuffFilledDataSize() > 0){
        __raiseEv(evWaitReceiver);
        return false;
    }
    
    if( false == __trSend(COMMAND_POST_SERVER_UPDATE, sizeof(COMMAND_POST_SERVER_UPDATE) - 1 ) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
    return true;
            
}

/************************************************************************
 * STATIC CALL BACKS
 ***********************************************************************/
//Parser_OnMsg
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len) {
    
    if(code == (Parser_Codes)parserCode_Ok) {
        switch(__state){
            case stTurnOffEcho:{
                //exitSt_TurnOffEcho();
                enterSt_setWifiMode(__espMode);
                break;
            }
            case stSetWifiMode:{
                //==
                switch(__espMode){
                    case communicator_espModeStation:{
                        enterSt_connectToAp();
                        break;
                    }
                    case communicator_espModeAccessPoint:{
                        enterSt_setAp();
                        break;
                    }
                    case communicator_espModeDual:{
                        break;
                    }
                    default:{
                        
                    }
                }
                //==
                
                break;
            }
            case stJoinAp:{
                enterState_connectServer();
                break;
            }
            case stConnectServer:{
                enterState_setMsgLength();
                break;
            }
            case stSeMsgLength:{
                enterState_updateServer();
                break;
            }
            default:
                break;
        }
    } else if(code == (Parser_Codes)parserCode_Json ){
            jsonParser_analyse((char*)&data[len - 7]);  //Should Point to "}"
    } else if( code == (Parser_Codes)parserCode_Ready ) {
        __clearAllEvents();
        enterSt_turnOffEcho();
    } else {
        
    }
    
     receiver_resetFrBuff();

}

//static uint8_t enterState(State st){
//    
//}