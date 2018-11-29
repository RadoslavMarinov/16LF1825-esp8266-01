/* 
 * File:   transmitter-primary.h
 * Author: Riko
 *
 * Created on 17 ???????? 2018, 19:28
 */

#ifndef TRANSMITTER_PRIMARY_H
#define	TRANSMITTER_PRIMARY_H

#define MODULE_NAME transmitter

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif


typedef enum {
    stReady,
    stBusy,
}Transmitter_State;

typedef struct{
    void (*transmitter_readyCb)(void);
    Transmitter_State state;
    uint8_t * data;
    uint8_t dataSize;
    uint8_t curIdx;
}Transmitter_Self;

/*********************************************************
 * ON READY CALL BACK
 *********************************************************/
#define ON_ReadyCb     (transmitter_self.transmitter_readyCb)
#define SET_OnReadyCb(cb)   do{ ON_ReadyCb = (cb); }while(0)
/*********************************************************
 * STATE
 *********************************************************/
#define SET_State(st)   do{ transmitter_self.state = (st); }while(0)
#define GET_State()     (transmitter_self.state)
#define IS_State(st)    (st == transmitter_self.state ? true : false )

/*********************************************************
 * DATA POINTER
 *********************************************************/
#define GET_DataPointer()   (transmitter_self.data)
#define SET_DataPointer(p)  do{ transmitter_self.data = (p); }while(0)
#define GET_DataAt(idx)     ( GET_DataPointer()[idx] )
//#define
/*********************************************************
 * DATA SIZE
 *********************************************************/
#define SET_DataSize(size)  do{ transmitter_self.dataSize = (size); }while(0)
#define GET_DataSize()      (transmitter_self.dataSize)
//#define
/*********************************************************
 * CURRENT INDEX
 *********************************************************/
#define GET_CurIdx()      ( transmitter_self.curIdx )
#define SET_CurIdx(num)   do{ transmitter_self.curIdx = (num); }while(0);
#define INCR_CurIdx()     do{ transmitter_self.curIdx++; }while(0);
//#define

/*********************************************************
 * DEPENDENCIES
 *********************************************************/
#define SEND_Byte(b)     (( PIR1bits.TXIF ?  TX1REG = (b) :  void ), IS_UartTxReady())
#define USART_Send(b)   do{ TX1REG = (b); }while(0)
#define USART_EnableTxInter()   do{  PIE1bits.TXIE = 1; }while(0)
#define USART_DisableTxInter()   do{  PIE1bits.TXIE = 0; }while(0)
#define IS_UartTxReady()    (PIR1bits.TXIF ? true : false)
#endif	/* TRANSMITTER_PRIMARY_H */

