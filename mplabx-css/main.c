/* 
 * File:   main.c
 * Author: Radoslav Marinov
 *
 * Created on 04 10 2018, 14:57
 */
#include <16LF1825.h>
#include <stdint.h>
/*
 * 
 */
#fuses INTRC_IO, NOWDT,NOMCLR, NOCLKOUT, PLL
#USE DELAY (int=32MHZ, PLL_WAIT)

#USE RS232 (UART1, BAUD=115200)

void main(void) {
    disable_interrupts(GLOBAL);
    enable_interrupts(INT_RDA);
//    enable_interrupts(INT_TBE); //If I comment this line the Rx works well and I see 'R' printed on the terminal
    enable_interrupts(GLOBAL);

    while(TRUE){
        output_high(PIN_C2);
        delay_ms(500);
        output_low(PIN_C2);
        delay_ms(500);
        putc('R');
        
    }
}

#INT_RDA
void Rx_Da_INT(void){
    char c;
    c = getc();
    putc(c);
}
#INT_TBE
void Tx_Be_INT(void){
    output_low(PIN_C2);
disable_interrupts(INT_TBE);
}
