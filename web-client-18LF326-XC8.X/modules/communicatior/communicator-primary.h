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

#ifndef CONF_SERVER_HOST
#error "Missing required CONF_SERVER_HOST"
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

#ifndef ESP_AP_IP
#error "Missing required ESP_AP_IP"
#endif 

#ifndef ESP_AP_GATEWAY
#error "Missing required ESP_AP_GATEWAY"
#endif 


#ifndef ESP_AP_SUBNET
#error "Missing required ESP_AP_SUBNET"
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
    stEnableDhcp,
    stSetApAddr,
    stSetConnsMultSingle,
    stConfServer,
    sthttpServer,
    stConnectServer, 
    stHttpClient,
    stSeMsgLength,
    stUpdateServer,
}State;

typedef struct{
    union {
    struct{
        unsigned int evInitEsp : 1;
        unsigned int evWaitReceiver : 1;
    };
    uint8_t evsCont;
    };
}Events;

typedef struct {
    unsigned int errTrBusy : 1; // When calling transmitter_send while busy
    unsigned int errEvWaitReceiverRaisedInWrongState : 1;
    unsigned int errEspErrorMessage : 1;
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
/******************** DISPATCHERS ********************/
static uint8_t dispatchEvInitEsp(void);
//static uint8_t dispatchEventWaitReceiver(void);
static uint8_t dispatchMsgOk(void);
/******************** HANDLERS ********************/
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len);
/******************** TRAMSITIONS ********************/
static void enterSt_turnOffEcho(void);
static void enterSt_setWifiMode(communicator_EspMode espMode);
static void enterSt_connectToAp(void);
static void enterSt_setAp(void);
static void enterState_enableDhcp(communicator_EspMode mode, uint8_t enable);
static void enterSt_setApAddr(void);
static void enterState_enableServerMultipleConnections(uint8_t yes);
static void enterState_confServer(const char *portStr);
static void enterState_httpServer(void);
static void enterState_connectServer(void);
static void enterState_httpClient(void);

static void handle_parserCodeFail(void);
// TIMER CALLBACKS
static void raiseServerEvStart(void);


/******************** OTHERS ********************/
static void communicator_initSelf(void);

static const char COMMAND_RESET[] = "AT+RST\r\n";
static const char COMMAND_TURN_OFF_ECHO[] = "ATE0\r\n";
static const char COMMAND_SET_MODE_STATION[] = "AT+CWMODE=1\r\n";
static const char COMMAND_SET_MODE_ACCESS_POINT[] = "AT+CWMODE=2\r\n";

static const char COMMAND_SET_AP[]  = 
    "AT+CWSAP=\""ESP_AP_SSID"\",\""ESP_AP_PWD"\","ESP_AP_CH","ESP_AP_ENC"\r\n";
//"AT+CWSAP=\"esp_123\",\"1234test\",5,3\r\n";

static const char COMMAND_SET_AP_ADDR[] = 
     "AT+CIPAP_DEF=\"" ESP_AP_IP "\",\""  ESP_AP_GATEWAY "\",\"" ESP_AP_SUBNET "\"\r\n";

static const char COMMAND_SET_MULT_CONNS[] = "AT+CIPMUX=1\r\n";
static const char COMMAND_SET_SINGLE_CONN[] = "AT+CIPMUX=0\r\n";






#endif	/* COMMUNICATOR_PRIMARY_H */

