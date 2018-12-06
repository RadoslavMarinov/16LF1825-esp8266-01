/* 
 * File:   server.h
 * Author: Riko
 *
 * Created on 04 ???????? 2018, 13:27
 */

#ifndef SERVER_H
#define	SERVER_H

typedef enum {
    server_routeInvalid,
    server_routeRoot,
            
}server_Routes;

uint8_t server_task(void);

void server_raiseEventSendData(server_Routes route);
void server_raiseEventMsgOk(void);
void server_raiseEventCloseTcpOk(void);

#endif	/* SERVER_H */

