#include "../../config.h"
#include "transmitter-primary.h"
#include "transmitter.h"

volatile static Transmitter_Self transmitter_self;

void transmitter_init(void){
    SET_State(stReady);
//    transmitter_self.state =stReady;
}

uint8_t transmitter_send(uint8_t * data, uint8_t length){
//    SEND_Byte('R');
//    TX1REG = 'R';
    PIE1bits.TXIE = 1;
    if(IS_State(stReady)){
        return true;
    } else {
        return false;
    }
}