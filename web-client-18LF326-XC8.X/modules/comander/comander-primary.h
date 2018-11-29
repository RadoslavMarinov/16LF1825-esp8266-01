/* 
 * File:   comander-primary.h
 * Author: Riko
 *
 * Created on 24 ???????? 2018, 19:36
 */

#ifndef COMANDER_PRIMARY_H
#define	COMANDER_PRIMARY_H

#include "comander.h"


#define COMMAND_NOT_FOUND 0xFFFFU

#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(esp);}while(0)
#else
    #define __addGlobalError()   
#endif

#ifndef JSON_KEY_MAX_LEN
#error "Missing required: JSON_KEY_MAX_LEN "
#endif

#ifndef JSON_VAL_MAX_LEN
#error "Missing required: JSON_VAL_MAX_LEN "
#endif

#define __getMapChar(unitIdx, charOffset)   \
    (commandMap.commander_commands[unitIdx].command[charOffset])
#define __getCallBack(unitIdx)                \
    ( commandMap.commander_commands[unitIdx].fp)
#define __runMapCallBack( unitIdx, ... )    \
    ( commandMap.commander_commands[unitIdx].fp( __VA_ARGS__ ) )


static int16_t commander_find(char *command);

#endif	/* COMANDER_PRIMARY_H */

