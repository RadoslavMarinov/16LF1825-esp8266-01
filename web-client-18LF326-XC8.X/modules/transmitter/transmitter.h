/* 
 * File:   transmitter.h
 * Author: Riko
 *
 * Created on 17 ???????? 2018, 19:28
 */

#ifndef TRANSMITTER_H
#define	TRANSMITTER_H

void transmitter_init(void(*onReady)(void));
uint8_t transmitter_sendNext(void);
uint8_t transmitter_send(uint8_t * data, uint8_t length);

#endif	/* TRANSMITTER_H */

