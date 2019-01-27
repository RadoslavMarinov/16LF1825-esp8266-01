#include "../../config.h"
#include "transmitter-primary.h"
#include "transmitter.h"

volatile static Transmitter_Self transmitter_self;

void transmitter_init(void(*onReady)(void)){
    SET_OnReadyCb(NULL);
    SET_State(stReady);
    SET_CurIdx(0);
    SET_DataSize(0);
//    transmitter_self.state =stReady;
}

//
uint8_t transmitter_isBusy(void){
    return IS_State(stBusy);
}

uint8_t transmitter_send(uint8_t * data, uint16_t length){
//    SEND_Byte('R');
//    TX1REG = 'R';
//    PIE1bits.TXIE = 1;
    if(IS_State(stReady) && length > 0){
        SET_State(stBusy);
        SET_DataSize(length);
        SET_DataPointer(data);
        SET_CurIdx(0);
        return transmitter_sendNext();
    } else {
        CONF_raiseNvErrBit(conf_nvErr_transmitter_sendWhileBusy);
        return false;
    }
}

uint8_t transmitter_sendNext(void){
    if(GET_DataSize() > GET_CurIdx() ){
        USART_Send(GET_DataAt(GET_CurIdx()));
        INCR_CurIdx();
        USART_EnableTxInter();
        return true;
    } else{
        USART_DisableTxInter();
        SET_State(stReady);
        return false;
    }
}