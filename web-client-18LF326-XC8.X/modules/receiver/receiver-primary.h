/* 
 * File:   receiver-primary.h
 * Author: Riko
 *
 * Created on 15 ???????? 2018, 12:10
 */

#ifndef RECEIVER_PRIMARY_H
#define	RECEIVER_PRIMARY_H

#include <stdint.h>

#define MODULE_NAME receiver

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif


/* Init data structure  */
#define RECEIVER_CIRC_BUFFER_SIZE 256U
#define RECEIVER_FRAME_BUFF_SIZE 512U

/* Typedefs */
// EVENTS
typedef uint8_t Event;
typedef uint8_t CircBuffArr[RECEIVER_CIRC_BUFFER_SIZE];
typedef uint8_t FrameBuffData[RECEIVER_FRAME_BUFF_SIZE];

// STATE
typedef enum {
    off,
}State;

// ERRORS
typedef struct {
    unsigned int circBuffOverflown :1;
    unsigned int circBuffOverPop :1; // Trying to pop more than CircBuff is filled with
    unsigned int frameBuffOverflow :1;
    unsigned int uart_overrun :1;
}Errors;

// Cic Buffer
typedef struct {
    uint16_t head;
    uint16_t tail;
    CircBuffArr buff;
}CircBuff;

typedef struct {
    uint16_t size;
    FrameBuffData data;
    unsigned int locked : 1;
}FrameBuff;

typedef struct {
    Event ev;
    State st;
    Errors err;
    CircBuff cb;
    FrameBuff frBuff;
    void * onMessage;
}SelfData;

/* Circular Buffer */

#define cBuff                   (receiver_self.cb.buff)
#define cBuffHead               (receiver_self.cb.head)
#define cBuffTail               (receiver_self.cb.tail)
#define cBuffGetChar(idx)       ( cBuff[idx] )


/* Circular Buffer */
#define CbError                 (receiver_self.err)
#define SET_err(err)            do{ CbError.err = 1; __addGlobalError();}while(0)    
#define CLEAR_err(err)            do{ CbError.err = 0; }while(0)    

/* FRAME BUFFER*/
#define FRAME_Buff              (receiver_self.frBuff)
#define frBuffData              (FRAME_Buff.data)
#define frBuffSize              (FRAME_Buff.size)
#define frBuffLocked            (FRAME_Buff.locked)
//Methods
#define LOCK_frameBuff()        do{ frBuffLocked = 1; }while(0)
#define UNLOCK_frameBuff()      do{ frBuffLocked = 0; }while(0)


#define __onMessage             ( receiver_self.onMessage )
#define __setOnMsg(cb)          do{ __onMessage = (cb); }while(0)

/* UART */
#define ENABLE_RxInterrupt()    do{ PIE1bits.RCIE = 1; }while(0)
#define DISABLE_RxInterrupt()   do{ PIE1bits.RCIE = 0; }while(0)
#define ENABLE_TxInterrupt()    do{ PIE1bits.TXIE = 1; }while(0)
#define DISABLE_TxInterrupt()   do{ PIE1bits.TXIE = 0; }while(0)

#define __enable_continReceive()    do{ RC1STAbits.CREN  = 1; }while(0)
#define __disable_continReceive()   do{ RC1STAbits.CREN  = 0; }while(0)

#define __enable_rxInterrupt()    do{ PIE1bits.RCIE = 1; }while(0)
#define __disable_rxInterrupt()    do{ PIE1bits.RCIE = 0; }while(0)

#define __enable_interrupts()       do{__enable_rxInterrupt(); __enable_continReceive();}while(0)
#define __disable_interrupts()       do{__disable_rxInterrupt(); __disable_continReceive();}while(0)
#endif	/* RECEIVER_PRIMARY_H */


