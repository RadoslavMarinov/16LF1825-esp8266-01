#include "../../config.h"
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
    transmitter_send((uint8_t*)COMMAND_RESET, sizeof(COMMAND_RESET));
    __setState(stReset);
    return true;
}

/************************************************************************
 * STATE TRANSITION
 ***********************************************************************/
static void enterSt_turnOffEcho(void){
    __setState(stTurnOffEcho);
    transmitter_send((uint8_t*)COMMAND_TURN_OFF_ECHO, sizeof(COMMAND_TURN_OFF_ECHO));
//    receiver_start();
//    WAIT RESPONSE "OK"
}

static void enterSt_setWifiMode(void){
    __setState(stSetWifiMode);
    if(false == __trSend(COMMAND_SET_MODE_STATION)){
        __raiseErr(errTrBusy);
        #ifdef UNDER_TEST
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