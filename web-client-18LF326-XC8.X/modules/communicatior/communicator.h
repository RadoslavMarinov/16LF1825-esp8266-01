/* 
 * File:   communicator.h
 * Author: Riko
 *
 * Created on 17 ???????? 2018, 19:17
 */

#ifndef COMMUNICATOR_H
#define	COMMUNICATOR_H

typedef enum{
    communicator_espModeStation,
    communicator_espModeAccessPoint,
    communicator_espModeDual,
}communicator_EspMode;

void communicator_init(uint8_t startReceiver, communicator_EspMode espMode);
uint8_t communicator_task(void);
void communicator_initEsp(void);


#endif	/* COMMUNICATOR_H */

