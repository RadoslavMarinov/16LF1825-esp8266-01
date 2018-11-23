#include "../../config.h"
#include "../eeprom/eeprom.h"
#include "communicator-primary.h"
#include "communicator.h"
#include "../receiver/receiver.h"
#include "../transmitter/transmitter.h"
#include "../parser/parser.h"
#include "../parser/json-parser/json-parser.h"

Self comm_self;

uint8_t communicator_task(void){
    uint8_t didWork = false;
    if( __isPendingEv() ) {
        if( __isRaisedEv(evReset) ){
            didWork = dispatchEvReset();
        }
    }
    return didWork;
}


void communicator_init(uint8_t start){
    communicator_initSelf();
    receiver_init(handleMessage);
    transmitter_init(NULL);
//    parser_init(handleMessage);
    if(start){
        __raiseEv(evReset);
    }
}

static void communicator_initSelf(void){
    __clearAllEvents();
    __setState(stOff);

}

/************************************************************************
 * EVENT DISPATCHERS
 ***********************************************************************/
static uint8_t dispatchEvReset(void) {
    return handleEvReset();
}

/************************************************************************
 * EVENT HANDLERS
 ***********************************************************************/
static uint8_t handleEvReset(void){
    communicator_init(false);
    transmitter_send((uint8_t*)COMMAND_RESET, sizeof(COMMAND_RESET) - 1);
    __setState(stReset);
    return true;
}

/************************************************************************
 * STATE TRANSITION
 ***********************************************************************/
static void enterSt_turnOffEcho(void){
    __setState(stTurnOffEcho);
    transmitter_send((uint8_t*)COMMAND_TURN_OFF_ECHO, sizeof(COMMAND_TURN_OFF_ECHO) - 1);
//    receiver_start();
//    WAIT RESPONSE "OK"
}

static void enterSt_setWifiMode(void){
    __setState(stSetWifiMode);
    if(false == __trSend(COMMAND_SET_MODE_STATION, sizeof(COMMAND_SET_MODE_STATION) - 1 )){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
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

static void enterState_connectServer(){
    __setState(stConnectServer);
    if( false == __trSend(COMMAND_CONNECT_SERVER, sizeof(COMMAND_CONNECT_SERVER)) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
}

static void enterState_setMsgLength(){
    uint16_t length;
    __setState(stSeMsgLength);
    
    if( false == __trSend("AT+CIPSEND=", 11) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
//    TODO : get this blocking shit out of here - it returns OK anyway - use it!
    while(transmitter_isBusy()){
        ;
    }
    sprintf(__txBuff, "%d\r\n", sizeof(COMMAND_POST_SERVER_UPDATE));
    length = strlen(__txBuff);
    if( false == __trSend(__txBuff, length) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }

    if( false == __trSend(COMMAND_POST_SERVER_UPDATE, sizeof(COMMAND_POST_SERVER_UPDATE)) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
}

/************************************************************************
 * CALL BACKS
 ***********************************************************************/
//Parser_OnMsg
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len) {
    
    if(code == (Parser_Codes)parserCode_Ok) {
        switch(__state){
            case stTurnOffEcho:{
                //exitSt_TurnOffEcho();
                enterSt_setWifiMode();
                break;
            }
            case stSetWifiMode:{
                enterSt_connectToAp();
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
            default:
                break;
        }
    } else if(code == (Parser_Codes)parserCode_Json ){
            jsonParser_analyse((char*)&data[len - 7]);  //Should Point to "}"
    } else if( code == (Parser_Codes)parserCode_Ready ) {
        receiver_clearErrorFrBuffOvrfl(); //FRame Buff Overflow Always happens onReset
        communicator_initSelf();
        enterSt_turnOffEcho();
    } else {
        
    }
    
     receiver_resetFrBuff();

}

//static uint8_t enterState(State st){
//    
//}