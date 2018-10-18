/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.  
#include <stdint.h>



/* Interfaces Declarations*/
void receiver_init(void);
void receiver_push(uint8_t data);
uint8_t receiver_pop(void);
uint16_t receiver_getCircBuffFilledDataSize(void);
uint8_t receiver_task(void);
void receiver_incrTail(void);
void receiver_push2FrameBuff(uint8_t data);


#endif	/* XC_HEADER_TEMPLATE_H */

