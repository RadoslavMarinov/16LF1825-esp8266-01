/* 
 * File:   transmitter-primary.h
 * Author: Riko
 *
 * Created on 17 ???????? 2018, 19:28
 */

#ifndef TRANSMITTER_PRIMARY_H
#define	TRANSMITTER_PRIMARY_H

typedef enum {
    stReady,
    stBusy,
}Transmitter_State;

typedef struct{
    Transmitter_State state;
}Transmitter_Self;

/*********************************************************
 * STATE
 *********************************************************/
#define SET_State(st)   do{ transmitter_self.state = (st); }while(0)
#define GET_State()     (transmitter_self.state)
#define IS_State(st)    (st == transmitter_self.state ? true : false )
/*********************************************************
 * DEPENDENCIES
 *********************************************************/
#define SEND_Byte(b)     (( PIR1bits.TXIF ?  TX1REG = (b) :  void ), PIR1bits.TXIF)
#endif	/* TRANSMITTER_PRIMARY_H */

