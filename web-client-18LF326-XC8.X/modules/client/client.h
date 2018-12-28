/* 
 * File:   client.h
 * Author: Riko
 *
 * Created on 09 ???????? 2018, 12:39
 */

#ifndef CLIENT_H
#define	CLIENT_H

typedef void (*client_OnError)(const char * err);

void client_init(client_OnError onErr);
uint8_t client_task(void);
uint8_t client_raiseEvStart(void);
uint8_t client_raiseEv_do(void);
uint8_t client_raiseEventMsgOk(void);
uint8_t client_raiseEvenUpdateServer(void);
uint8_t client_raiseEventError(void);
uint8_t client_raiseEventAck(void);

#endif	/* CLIENT_H */

