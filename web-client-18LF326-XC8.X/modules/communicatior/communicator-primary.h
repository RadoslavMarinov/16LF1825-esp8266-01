/* 
 * File:   communicator-primary.h
 * Author: Riko
 *
 * Created on 17 ???????? 2018, 19:17
 */

#ifndef COMMUNICATOR_PRIMARY_H
#define	COMMUNICATOR_PRIMARY_H

#include "string.h"
#include "../parser/parser.h"

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
    stConnectServer,  
    stSeMsgLength,
    stSendUpdateMessageToServer,
}State;

typedef struct{
    union {
    unsigned int evReset : 1;
    uint8_t evsCont;
    };
}Events;

typedef struct {
    unsigned int errTrBusy; // When calling transmitter_send while busy
}Errors;

typedef struct {
    uint16_t size;
    
}Message;

typedef struct {
    State state;
    Events events;
    Errors errors;
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
#define __raiseErr(err)     do{ __errors.err  = 1; }while(0)
#define __clearErr(err)     do{ __errors.err  = 0; }while(0)

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
static void communicator_initSelf(void);
static uint8_t handleEvReset(void);
static uint8_t dispatchEvReset(void);
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len);
static void enterState_turnOffEcho(void);
static void enterSt_connectToAp(void);
static void enterState_connectServer(void);
static void enterState_setMsgLength(void);

static const char COMMAND_RESET[] = "AT+RST\r\n";
static const char COMMAND_TURN_OFF_ECHO[] = "ATE0\r\n";
static const char COMMAND_SET_MODE_STATION[] = "AT+CWMODE=1\r\n";
static const char COMMAND_CONNECT_SERVER[] = "AT+CIPSTART=\"TCP\",\"electricity-manager1.herokuapp.com\",80\r\n";

static const char COMMAND_POST_SERVER_UPDATE[] = 
    "POST "CONF_SERVER_UPDATE_ROUTE" HTTP/1.1\r\nHost: "CONF_SERVER_HOST"\r\n\r\n";



#endif	/* COMMUNICATOR_PRIMARY_H */

