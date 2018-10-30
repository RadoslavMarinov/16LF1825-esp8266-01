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

#define COMMANDER_COMMAND_COUNT     10U
#define COMMAND_STR_MAX_LEN         JSON_KEY_MAX_LEN

typedef void (*Commander_fp)(void *);

typedef struct {
    char command[COMMAND_STR_MAX_LEN];
    Commander_fp fp;
}Comander_commandUnit;


typedef struct {
    Comander_commandUnit commander_commands[COMMANDER_COMMAND_COUNT];
}Commander_commandMap;


uint8_t commander_execute(char *command, void * value);


#endif	/* COMANDER_H */

