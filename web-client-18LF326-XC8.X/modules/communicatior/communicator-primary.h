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


typedef enum {
    stOff,
    stReset,
    stTurnOffEcho,
           
}State;

typedef struct{
    union {
    unsigned int evReset : 1;
    uint8_t evsCont;
    };
}Events;

typedef struct {
    uint16_t size;
    
}Message;

typedef struct {
    State state;
    Events events;
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

static void communicator_initSelf(void);
static uint8_t handleEvReset(void);
static uint8_t dispatchEvReset(void);
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len);
static void enterState_turnOffEcho(void);

static const char COMMAND_RESET[] = "AT+RST\r\n";
static const char COMMAND_TURN_OFF_ECHO[] = "ATE0\r\n";


#endif	/* COMMUNICATOR_PRIMARY_H */

