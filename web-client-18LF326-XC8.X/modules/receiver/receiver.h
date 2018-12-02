/* 
 * File:   
 * Author: 
 * Comments:
 * Revision history: 
 */

#ifndef XC_HEADER_TEMPLATE_H
#define	XC_HEADER_TEMPLATE_H

#include <xc.h> // include processor files - each processor file is guarded.
#include "../parser/parser.h"
#include <stdint.h>

typedef void(*Receiver_OnMsg)(Parser_Codes code, uint8_t * data, uint16_t len);
typedef Parser_Codes (*receiver_OnFrame)(char * data, uint16_t len);


/* Interfaces Declarations*/
void receiver_init(receiver_OnFrame onFrame, Receiver_OnMsg onMsg, uint8_t start);
void receiver_push(uint8_t data);
uint8_t receiver_pop(void);
uint16_t receiver_getCircBuffFilledDataSize(void);
uint8_t receiver_task(void);
void receiver_incrTail(void);
void receiver_push2FrameBuff(uint8_t data);
void receiver_stop(void);
void receiver_start(void);
void receiver_stopAndReset(void);
void receiver_resetFrBuff(void);
void receiver_resetCircBuff(void);


#endif	/* XC_HEADER_TEMPLATE_H */

