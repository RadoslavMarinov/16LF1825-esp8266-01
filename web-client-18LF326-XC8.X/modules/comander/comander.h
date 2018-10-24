/* 
 * File:   comander.h
 * Author: Riko
 *
 * Created on 24 ???????? 2018, 19:35
 */

#ifndef COMANDER_H
#define	COMANDER_H

#include "../../config.h"

#ifndef JSON_KEY_MAX_LEN
#error "Missing required: JSON_KEY_MAX_LEN "
#endif

#define COMMANDER_COMMAND_COUNT     2U
#define COMMAND_STR_MAX_LEN         JSON_KEY_MAX_LEN



typedef struct {
    char command[COMMAND_STR_MAX_LEN];
    void *fp;
}Comander_commandUnit;


typedef struct {
    Comander_commandUnit commander_commands[COMMANDER_COMMAND_COUNT];
}Commander_commandMap;





#endif	/* COMANDER_H */

