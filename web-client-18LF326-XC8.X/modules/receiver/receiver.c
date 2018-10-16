#include "../../config.h"
#include "receiver-primary.h"
#include "receiver.h"
#include "../parser/parser.h"

/* Variables Definition */
volatile static SelfData receiver_self;

//0x0D:CR ; 0x0A:NL receiver_incrTail
uint8_t receiver_task(void){
    uint8_t data;
    data = cBuffGetChar(cBuffTail);
    while(receiver_getCircBuffFilledDataSize() > 0) {
         data = cBuffGetChar(cBuffTail);
        if(data != 0x0D && data != 0x0A ) {
            receiver_push2FrameBuff(data);
            
        } else {
            parser_analyse((uint8_t *)receiver_self.frBuff.data, frBuffSize);
        }
         receiver_incrTail();
    }
    return 1;
    
}

/* Interfaces */
void receiver_init(){ 
    cBuffHead = 0;
    cBuffTail= 0; 
}

//HAVE SIDE EFECTS  - CARE WHEN USE !!!!!!!!!!!!!!!!!!!!!
void receiver_push(uint8_t data){
        
    #if defined(UNDER_TEST)
    if(cBuffHead == cBuffTail){ 
        SET_err(circBuffOverflown);
    }
    #endif 
    
    cBuff[cBuffHead] =  data;
    cBuffHead++;
    
    if(  cBuffHead >= sizeof(cBuff) ) { 
        cBuffHead = 0;
    }
}

//HAVE SIDE EFECTS  - CARE WHEN USE !!!!!!!!!!!!!!!!!!!!!
uint8_t receiver_pop(void){ 
    uint8_t data;
    
    
    if(cBuffTail == cBuffHead ) {
        #if defined(UNDER_TEST)
        SET_err(circBuffOverPop);
        #endif
        return 0xFF;
    }
    
    data = cBuff[cBuffTail];
    cBuffTail++;
    
    if(cBuffTail >= sizeof(cBuff)){
        cBuffTail= 0;
    }
    
    
    return data;
}

uint8_t receiver_getCircBuffFilledDataSize() {
    uint8_t size;
    
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
    }
}
