/* 
 * File:   communicator-primary.h
 * Author: Riko
 *
 * Created on 17 ???????? 2018, 19:17
 */

#ifndef COMMUNICATOR_PRIMARY_H
#define	COMMUNICATOR_PRIMARY_H

#include "string.h"
#include "communicator.h"
#include "../parser/parser.h"

#define MODULE_NAME communicator

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif

#ifndef ESP_AP_SSID
#error "Missing required ESP_AP_SSID"
#endif 

#ifndef ESP_AP_PWD
#error "Missing required ESP_AP_PWD"
#endif 

#ifndef ESP_AP_CH
#error "Missing required ESP_AP_CH"
#endif 

#ifndef ESP_AP_ENC
#error "Missing required ESP_AP_ENC"
#endif 


/******************************************************************************* 
 * 
 ******************************************************************************/


#define TX_MSG_SIZE                                 100U

typedef enum {
    tcp,
    udp,
}TransportProtocol;

typedef enum {
    stOff,
    stReset,
    stTurnOffEcho,
    stSetWifiMode,
    stJoinAp,
    stSetAp,
    stConnectServer,  
    stSeMsgLength,
    stUpdateServer,
}State;

typedef struct{
    union {
    struct{
        unsigned int evReset : 1;
        unsigned int evWaitReceiver : 1;
    };
    uint8_t evsCont;
    };
}Events;

typedef struct {
    unsigned int errTrBusy : 1; // When calling transmitter_send while busy
    unsigned int errEvWaitReceiverRaisedInWrongState : 1;
}Errors;

typedef struct {
    uint16_t size;
    
}Message;

typedef struct {
    State state;
    Events events;
    Errors errors;
    communicator_EspMode espMode;
    char txBuff[TX_MSG_SIZE];
}Self;


/********************************************************
 * STATES
 *******************************************************/
#define __state         ( comm_self.state )
#define __getState      ( comm_self.state )
#define __setState(st)  do{__state = (st);}while(0)


/********************************************************
 * EVENTS
 *******************************************************/
#define __events            (comm_self.events)
#define __evCont            (comm_self.events.evsCont)
#define __raiseEv(ev)       do{ __events.ev = 1; }while(0)
#define __clearEv(ev)       do{ __events.ev = 0; }while(0)
#define __isRaisedEv(ev)    ( __events.ev ? true : false )
#define __isPendingEv()     ( __evCont > 0 ? true : false )

#define __clearAllEvents()  do{ memset(&__evCont, 0, sizeof(__evCont)); }while(0)
/********************************************************
 * ERRORS
 *******************************************************/
#define __errors            (comm_self.errors)
#define __raiseErr(err)     do{ __errors.err  = 1;__addGlobalError(); }while(0)
#define __clearErr(err)     do{ __errors.err  = 0; }while(0)

/********************************************************
 * ESP MODE
 *******************************************************/
#define __espMode           (comm_self.espMode)
#define __setEspMode(mode)  do{__espMode = (mode);}while(0)
/********************************************************
 * TX Buffer
 *******************************************************/
#define __txBuff            ( comm_self.txBuff )


/********************************************************
 * REQUIRED INTERFACES
 *******************************************************/
#define __trSend(command, size)   (transmitter_send(((uint8_t*)command), size ))
#define CONSTRUCT_HEADER(method, route, host) \
#method " " #route " HTTP/1.1\r\nHost: " #host


/********************************************************
 * STATIC FUNCTION DECLARATIONS
 *******************************************************/
static uint8_t handleEvReset(void);
static uint8_t dispatchEvReset(void);
static uint8_t dispatchEventWaitReceiver(void);
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len);
static void enterState_turnOffEcho(void);
static void enterSt_setWifiMode(communicator_EspMode espMode);
static void enterSt_connectToAp(void);
static void enterSt_setAp(void);
static void enterState_connectServer(void);
static void enterState_setMsgLength(void);
static uint8_t enterState_updateServer(void);
static void communicator_initSelf(void);

static const char COMMAND_RESET[] = "AT+RST\r\n";
static const char COMMAND_TURN_OFF_ECHO[] = "ATE0\r\n";
static const char COMMAND_SET_MODE_STATION[] = "AT+CWMODE=1\r\n";
static const char COMMAND_SET_MODE_ACCESS_POINT[] = "AT+CWMODE=2\r\n";
static const char COMMAND_CONNECT_SERVER[] = "AT+CIPSTART=\"TCP\",\"electricity-manager1.herokuapp.com\",80\r\n";
static const char COMMAND_SET_AP[]  = 
    "AT+CWSAP=\""ESP_AP_SSID"\",\""ESP_AP_PWD"\","ESP_AP_CH","ESP_AP_ENC"\r\n";
//"AT+CWSAP=\"esp_123\",\"1234test\",5,3\r\n";

static const char COMMAND_POST_SERVER_UPDATE[] = 
    "POST "CONF_SERVER_UPDATE_ROUTE" HTTP/1.1\r\nHost: "CONF_SERVER_HOST"\r\n\r\n";



#endif	/* COMMUNICATOR_PRIMARY_H */

