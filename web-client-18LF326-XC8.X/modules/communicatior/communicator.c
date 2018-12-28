#include "../../config.h"
#include "../eeprom/eeprom.h"
#include "../timer/timer.h"
#include "communicator-primary.h"
#include "communicator.h"
#include "../receiver/receiver.h"
#include "../transmitter/transmitter.h"
#include "../parser/parser.h"
#include "../parser/json-parser/json-parser.h"
#include "../client/client.h"
#include "../server/server.h"

Self comm_self;


/************************************************************************
 * GLOBAL METHODS
 ***********************************************************************/
uint8_t communicator_task(void){
    uint8_t didWork = false;
    if( __isPendingEv() ) {
        if( __isRaisedEv(evInitEsp) ){
            __clearEv(evInitEsp);
            didWork = dispatchEvInitEsp();
        }
    }
    return didWork;
}


void communicator_init(uint8_t startReceiver, communicator_EspMode espMode){
    
    __setEspMode(espMode);
    communicator_initSelf();
    receiver_init(parser_analyse, handleMessage, startReceiver);
    transmitter_init(NULL);   
    switch(espMode){
        case communicator_espModeStation:{
            client_init();
            break;
        }
        case communicator_espModeAccessPoint:{
            server_init();
            break;
        } default :{
            
        }
    }
}

void communicator_initEsp(void){
    __raiseEv(evInitEsp);
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
static uint8_t dispatchEvInitEsp(void){
    enterSt_turnOffEcho();
    return true;
}

static uint8_t dispatchMsgOk(void) {
    switch(__state){
        //------------ STATE
        case stTurnOffEcho:{
            //exitSt_TurnOffEcho();
            enterSt_setWifiMode(__espMode);
            break;
        }
        //------------ STATE
        case stSetWifiMode:{
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
            break;
        }
        //------------ STATE
        case stSetAp:{
            enterState_enableDhcp(communicator_espModeAccessPoint, true);
            break;
        }
        //------------ STATE
        case stEnableDhcp:{
            enterSt_setApAddr();
            break;
        }
        //------------ STATE
        case stSetApAddr:{
            enterState_enableServerMultipleConnections(true);
            break;
        }
        //------------ STATE
        case stSetConnsMultSingle:{
            enterState_confServer("80");
            break;
        }

        //------------ STATE
        case stConfServer:{
            enterState_httpServer();
            break;
        }

        //------------ STATE
        case stJoinAp:{
            enterState_httpClient();
            break;
        }
        //------------ STATE
//        case stConnectServer:{
//            enterState_httpClient();
//            break;
//        }
        //------------ STATE
        default:
            break;
        //------------
    }
    return 0;
}

/************************************************************************
 * STATIC EVENT HANDLERS
 ***********************************************************************/


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

static void enterState_enableDhcp(communicator_EspMode mode, uint8_t enable){
    __setState(stEnableDhcp);
    strcpy(__txBuff, "AT+CWDHCP=");
    // Append first argument
    switch(mode){
        case communicator_espModeStation:{
            strcat(__txBuff, "1,");
            break;
        } 
        case communicator_espModeAccessPoint:{
            strcat(__txBuff, "0,");
            break;
        }
        case communicator_espModeDual: {
            strcat(__txBuff, "2,");
            break;
        }
        default:{
            
        }
    }
    // Append second argument
    if(enable){
        strcat(__txBuff, "1\r\n");
    } else {
        strcat(__txBuff, "0\r\n");
    }
    // Send the string
    if( false == __trSend(__txBuff, strlen(__txBuff)) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
    
}

static void enterSt_setApAddr(void){
    __setState(stSetApAddr);
    if( false == __trSend(COMMAND_SET_AP_ADDR, sizeof(COMMAND_SET_AP_ADDR) - 1) ){
            #ifdef UNDER_TEST
            __raiseErr(errTrBusy);
            CONFIG_stopHere();
            #endif
        } 
}

static void enterState_enableServerMultipleConnections(uint8_t yes){
    __setState(stSetConnsMultSingle);
    if(yes){
        if( false == __trSend(COMMAND_SET_MULT_CONNS, sizeof(COMMAND_SET_MULT_CONNS) - 1) ){
            #ifdef UNDER_TEST
            __raiseErr(errTrBusy);
            CONFIG_stopHere();
            #endif
        }   
    } else {
        if( false == __trSend(COMMAND_SET_SINGLE_CONN, sizeof(COMMAND_SET_SINGLE_CONN) - 1) ){
            #ifdef UNDER_TEST
            __raiseErr(errTrBusy);
            CONFIG_stopHere();
            #endif
        } 
    }
}

static void enterState_confServer(const char *portStr){
    __setState(stConfServer);
    strcpy( (char*)__txBuff, "AT+CIPSERVER=1,");
    strcat(__txBuff, portStr);
    strcat(__txBuff, "\r\n");
    if( false == __trSend(__txBuff, strlen(__txBuff)) ){
        #ifdef UNDER_TEST
        __raiseErr(errTrBusy);
        CONFIG_stopHere();
        #endif
    }
}

static void enterState_httpServer(void){
    __setState(sthttpServer);
    receiver_setOnFrameCb(parser_httpServer);
}

static void enterState_httpClient(void){
    __setState(stHttpClient);
    receiver_setOnFrameCb(parser_httpClient);
    client_raiseEvStart();
}

/************************************************************************
 * STATIC CALL BACKS
 ***********************************************************************/
//Parser_OnMsg
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len) {
    
    switch(code){
        /***************** CODE OK ********************/
        case parserCode_Ok:{
            dispatchMsgOk();
            break;
        }
        /***************** CODE SERVER ACL ********************/
        case parserCode_serverAck:{
            timer_start(timer_getTicksFromSeconds(5), raiseServerEvStart);
            break;
        }
        /***************** CODE READY ********************/
        case parserCode_Ready:{
            __clearAllEvents();
            enterSt_turnOffEcho();
            break;
        }
        /***************** CODE  ERROR ********************/
        case parserCode_Error:{
            CONF_raiseNvErrBit(conf_nvErr_communicator_espErrMsg);
            __raiseErr(errEspErrorMessage);
            break;
        }
        /***************** CODE  FAIL ********************/
        case parserCode_fail:{
            handle_parserCodeFail();
            break;
        }
        default:{
            break;
        }
    }
    
    receiver_resetFrBuff();
}


// HADLERS -----------------
static void handle_parserCodeFail(void){
    switch (__state){
        case stJoinAp:{
            CONF_raiseNvErrBit(conf_nvErr_communicator_joinApFailed);
            SYSTEM_softReset();
            break;
        }
        default:{
        
        }
    }
}

// TIMER CALLBACKS
static void raiseServerEvStart(void){
    enterState_httpClient();
}