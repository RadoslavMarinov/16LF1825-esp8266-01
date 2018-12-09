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

        if( data == 0x0D || data == 0x0A ) {
            if(frStarted){
                receiver_push2FrameBuff('\0');
                p_code =  __onFrame((char*)frBuffData,  frBuffSize) ;
                if( p_code != parserCode_Unknown ) {
                    //Resets frame buffer, starts to fill from 0
                    ((Parser_OnMsg)__onMessage)(p_code, (uint8_t*)frBuffData, frBuffSize);
                     
                }
                frStarted  = 0;
                
            }
        } else {
            receiver_push2FrameBuff(data);
            frStarted = 1;
        }
        
        receiver_incrTail();
    }
    return didSomeWork;
}

/* Interfaces */
void receiver_init(receiver_OnFrame onFrame, Receiver_OnMsg onMsg, uint8_t start){
    if(onMsg){
        __setOnMsg(onMsg);
    }
    if(onFrame != NULL){
        __setOnFrame(onFrame);
    }
    receiver_resetCircBuff();
    receiver_resetFrBuff();
    if(start){
        receiver_start();
    } else {
        receiver_stop();
    }
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

void receiver_resetCircBuff(void){
    cBuffTail = cBuffHead  = 0;
}

void receiver_resetFrBuff(void){
    frBuffLocked = false;
    frBuffSize = 0;
}

//
void receiver_setOnFrameCb(receiver_OnFrame onFrame){
    __setOnFrame(onFrame);
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
    cBuffTail++;
    if(cBuffTail >= sizeof(cBuff)){
        cBuffTail= 0;
    }
    
}

void receiver_push2FrameBuff(uint8_t data){
    frBuffData[frBuffSize++] = data;
    if(frBuffSize >= sizeof(frBuffData)){
        SET_err(frameBuffOverflow);
        receiver_resetFrBuff();
        #ifdef UNDER_TEST
            CONFIG_stopHere();
        #endif
    }
}
