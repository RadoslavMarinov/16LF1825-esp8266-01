/* 
 * File:   client-primary.h
 * Author: Riko
 *
 * Created on 09 ???????? 2018, 12:40
 */

#ifndef CLIENT_PRIMARY_H
#define	CLIENT_PRIMARY_H

#include "../../config.h"
#include "client.h"
#include "../timer/timer.h"

#ifndef CLIENT_HEADER_MAX_SIZE
#error "Missing required CLIENT_HEADER_MAX_SIZE"
#endif

#ifndef CLIENT_BODY_MAX_SIZE
#error "Missing required CLIENT_BODY_MAX_SIZE"
#endif


#ifndef GET_SW1_VALUE
#error "Missing required GET_SW1_VALUE()"
#endif

#ifndef GET_SW2_VALUE
#error "Missing required GET_SW2_VALUE()"
#endif




typedef enum{
    code_didSomeWork,
    code_didNothing,
    code_done,
}client_Code;

typedef struct {
    union {
        struct{
            unsigned int evStart;
            unsigned int evMsgOk;
            unsigned int evUpdateServer;
            unsigned int evAck;
            unsigned int evError;
        };
        uint16_t evCont;
    };
}client_Events;

typedef enum {
    stIdle = 0,
    stConnectServer,
    stClosingTcpConnection,
    stUpdateServer,
}client_State;

typedef struct {
    union{
        struct {
            unsigned int erEvDoRaiseOvrfl : 1;
            unsigned int erEvErrorAtWrongState : 1;
            unsigned int erEvevMsgOkRaiseOvrfl : 1;
            unsigned int erEvevStartRaisedInWrongState : 1;
            unsigned int erEvevMsgOkRaisedInWrongState : 1;
            unsigned int erEventStartRaisedInWrongState : 1;
            unsigned int erEvevUpdateServerRaisedInWrongState : 1;
            unsigned int erEvevUpdateServerInWrongState : 1;
            unsigned int erTrBusy : 1; //8
            unsigned int clientAckTimeout : 1; //9
            unsigned int clientUpdTimeout : 1; //10
            
        };
        uint16_t errCont;
    };
}client_Errors;

typedef enum {
    client_tmrServerAliveTimeout,
    client_tmrsNumber,
}client_Timers;

typedef struct {
    timer_Hook hook;
    unsigned int active:1;
}client_Timer;

typedef struct {
    client_Events events; 
    client_State state;
    client_Errors errors;
    client_Timer timers[client_tmrsNumber];
    client_OnError onErr;
    char txBuff[CLIENT_HEADER_MAX_SIZE + CLIENT_BODY_MAX_SIZE];
    char bodyBuff[CLIENT_BODY_MAX_SIZE];
}client_Self;

// == EVENTS
#define __events                        ( client_self.events )
#define __raiseEv(ev)                     do{  __events.ev  = 1; }while(0)
#define __clearEv(ev)                     do{  __events.ev  = 0; }while(0)
#define __isRaisedEv(ev)                ( __events.ev == 1 ? true : false  )
#define __clearAllEvs()                 do{ __events.evCont = 0; }while(0)

// == STATE
#define __state                         ( client_self.state )
#define __setSt(st)                     do{  __state = (st); }while(0)    
#define __inSt(st)                      (__state == (st) ? true : false )

// == ERRORS
#define __errors                        ( client_self.errors )
#define __raiseErr(err)                 do{__errors.err = 1;}while(0)

// == TIMERS
#define __timers                        (client_self.timers)
#define __timerEnable(tmr, tmrHook)     \
    do{ __timers[tmr].hook = (tmrHook); __timers[tmr].active = 1; }while(0)
#define __timerDisable(tmr)             do{ __timers[tmr].active = 0; }while(0)
#define __timerEnabled(tmr)             ( __timers[tmr].active ? true : false )
#define __timerGetHook(tmr)             ( __timers[tmr].hook )

// == ON ERROR - Callback function invoked by client when error happens
#define __onError                       (client_self.onErr)
#define __setOnErr(cb)                  do{ __onError = (cb); }while(0)
#define __callOnErr(errMsg)             do{ __onError(errMsg);  }while(0)
void __onErrDummy(const char * bla){}

// == TX BUFFER
#define __txBuff                        (client_self.txBuff)

// == BODY BUFF
#define __bodyBuff                      (client_self.bodyBuff)

//  == EVENT DSPATCHERS
static uint8_t dispatchEv_updateServer(void);
static uint8_t dispatchEv_evStart(void);
static uint8_t dispatchEv_evDo(void);
static uint8_t dispatchEv_evMsgOk(void);
static uint8_t dispatchEv_error(void);
static uint8_t dispatchEv_evAck(void);

// == EVENT HANDLERS
static uint8_t handleEv_updateServer(void);

//  == STATE TRANZITION 
static void enterSt_idle(void);
static uint8_t enterSt_connectServer(void);
static uint8_t enterSt_updateServer(void);
static void enterSt_closingTcpConnection(void);


// == CALBACKS ====================================
static void onServerAliveTimeout(void);

//  == OTHERS
static client_Code updateServer(void);
static uint16_t composePostUpdateBody(char* startAddr);
static uint16_t composePostUpdateHeader(char * stAddr, uint16_t bodySize);

#define HEADER_POST_UPDATE_SIZE "AT+CIPSEND=19\r\n"

static const char COMMAND_POST_SERVER_UPDATE_ST_LINE[] = 
"POST "CONF_SERVER_UPDATE_ROUTE" HTTP/1.1\r\nHost: "CONF_SERVER_HOST"\r\n";





#endif	/* CLIENT_PRIMARY_H */

