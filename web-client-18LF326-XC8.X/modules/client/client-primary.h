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
            unsigned int evDo;
            unsigned int evMsgOk;
        };
        uint16_t evCont;
    };
}client_Events;

typedef enum {
    stIdle,
    stUpdateServer,
}client_State;

typedef struct {
    unsigned int erEvDoRaiseOvrfl;
    unsigned int erEvevMsgOkRaiseOvrfl;
    unsigned int erEvevMsgOkRaisedInWrongState;
}client_Errors;

typedef struct {
    client_Events events; 
    client_State state;
    client_Errors errors;
    char txBuff[CLIENT_HEADER_MAX_SIZE + CLIENT_BODY_MAX_SIZE];
    char bodyBuff[CLIENT_BODY_MAX_SIZE];
}client_Self;

// == EVENTS
#define __events                        ( client_self.events )
#define __raiseEv(ev)                     do{  __events.ev  = 1; }while(0)
#define __clearEv(ev)                     do{  __events.ev  = 0; }while(0)
#define __isRaisedEv(ev)                ( __events.ev == 1 ? true : false  )

// == STATE
#define __state                         ( client_self.state )
#define __setSt(st)                     do{  __state = (st); }while(0)    
#define __inSt(st)                      (__state == (st) ? true : false )

// == ERRORS
#define __errors                        ( client_self.errors )
#define __raiseErr(err)                 do{ __errors.err = 1; CONFIG_raiseError(client); }while(0)

// == TX BUFFER
#define __txBuff                        (client_self.txBuff)

// == BODY BUFF
#define __bodyBuff                      (client_self.bodyBuff)

//  == EVENT DSPATCHERS

static uint8_t dispatchEv_evStart(void);
static uint8_t dispatchEv_evDo(void);
static uint8_t dispatchEv_evMsgOk(void);

//  == STATE TRANZITION 
static void enterSt_updateServer(void);

//  == OTHERS
static client_Code updateServer(void);
static uint16_t composePostUpdateBody(char* startAddr);
static uint16_t composePostUpdateHeader(char * stAddr, uint16_t bodySize);

#define HEADER_POST_UPDATE_SIZE "AT+CIPSEND=19\r\n"

static const char COMMAND_POST_SERVER_UPDATE_ST_LINE[] = 
"POST "CONF_SERVER_UPDATE_ROUTE" HTTP/1.1\r\nHost: "CONF_SERVER_HOST"\r\n";





#endif	/* CLIENT_PRIMARY_H */

