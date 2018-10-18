#include "../../config.h"
#include "communicator-primary.h"
#include "communicator.h"
#include "../receiver/receiver.h"
#include "../transmitter/transmitter.h"
#include "../parser/parser.h"

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
    parser_init(handleMessage);
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
 * CALL BACKS
 ***********************************************************************/
//Parser_OnMsg
static void handleMessage(Parser_Codes code, uint8_t * data, uint16_t len) {
    
}

//static uint8_t enterState(State st){
//    
//}