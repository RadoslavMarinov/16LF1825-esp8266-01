#include "../../config.h"
#include "receiver.h"
#include "receiver-primary.h"
#include "../parser/parser.h"

/* Variables Definition */
volatile static SelfData receiver_self;

//0x0D:CR ; 0x0A:NL receiver_incrTail
uint8_t receiver_task(void){
    uint8_t data, didSomeWork = 0/* NO */;
    static uint8_t frStarted = 0;
    Parser_Codes p_code;
    while(receiver_getCircBuffFilledDataSize() > 0){
        didSomeWork = 1;  //YES
        data = cBuffGetChar(cBuffTail);

        if( data == 0x0D || data == 0x0A ){
            if(frStarted){
                receiver_push2FrameBuff('\0');
                p_code =  parser_analyse( (uint8_t *)frBuffData,  frBuffSize) ;
                if( p_code != parserCode_Unknown ) {
                    cBuffHead = cBuffTail;
                    receiver_stop();
                    ((Parser_OnMsg)__onMessage)(p_code, (uint8_t*)frBuffData, frBuffSize);
                    receiver_resetFrBuff();
                    frStarted  = 0;
                    return true;
                }
                frStarted  = 0;
                
            }
             receiver_incrTail();
        } else {
            receiver_push2FrameBuff(data);
            receiver_incrTail();
            frStarted = 1;
        }
    }
    return didSomeWork;
}

/* Interfaces */
void receiver_init(Receiver_OnMsg onMsg){
    __setOnMsg(onMsg);
    receiver_resetFrBuff();
    receiver_start();
    cBuffHead = 0;
    cBuffTail= 0; 
}

void receiver_start(void){
    volatile uint8_t dummy = 0;
    dummy  = RC1REG;    //clear Rx Interrupt flag by reading the data register
    if(dummy) dummy = 0;    //Prevent optimisation 
    __enable_continReceive();
    __enable_rxInterrupt();
}

void receiver_stop(void){
    volatile uint8_t dummy = 0;
    __disable_continReceive();
    __disable_rxInterrupt();
    dummy  = RC1REG;    //clear Rx Interrupt flag by reading the data register
    if(dummy) dummy = 0;    //Prevent optimisation 
}

static void receiver_resetFrBuff(void){
    frBuffLocked = false;
    frBuffSize = 0;
}
//HAVE SIDE EFECTS  - CARE WHEN USE !!!!!!!!!!!!!!!!!!!!!
void receiver_push(uint8_t data){
        
    cBuff[cBuffHead] =  data;
    cBuffHead++;
    
    if(  cBuffHead >= sizeof(cBuff) ) { 
        cBuffHead = 0;
    }
    
    #if defined(UNDER_TEST)
    if(cBuffHead == cBuffTail){ 
        SET_err(circBuffOverflown);
    }
    #endif 
    
}

//HAVE SIDE EFECTS  - CARE WHEN USE !!!!!!!!!!!!!!!!!!!!!
//uint8_t receiver_pop(void){ 
//    uint8_t data;
//    
//    
//    if(cBuffTail == cBuffHead ) {
//        #if defined(UNDER_TEST)
//        SET_err(circBuffOverPop);
//        #endif
//        return 0xFF;
//    }
//    
//    data = cBuff[cBuffTail];
//    cBuffTail++;
//    
//    if(cBuffTail >= sizeof(cBuff)){
//        cBuffTail= 0;
//    }
//    
//    
//    return data;
//}

uint16_t receiver_getCircBuffFilledDataSize() {
    uint16_t size;
    
    if( cBuffTail > cBuffHead ) {
        size = cBuffHead + sizeof(cBuff) - cBuffTail;
    } else {
        size = cBuffHead - cBuffTail;
    }
    
    return size;
}

void receiver_incrTail(){
    
    if(cBuffTail >= sizeof(cBuff)){
        cBuffTail= 0;
    } else {
        cBuffTail++;
    }
    
}

void receiver_push2FrameBuff(uint8_t data){
    frBuffData[frBuffSize++] = data;
    if(frBuffSize > sizeof(frBuffData)){
        SET_err(frameBuffOverflow);
        receiver_resetFrBuff();
    }
}
