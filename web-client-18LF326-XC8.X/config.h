/* 
 * File:   config.h
 * Author: Riko
 *
 * Created on 15 ???????? 2018, 12:05
 */

#ifndef CONFIG_H
#define	CONFIG_H

#include <stdint.h>
#include <stdio.h>
#include "string.h"
#include <xc.h>
#include <stdbool.h>

/* CONDITIONAL COMPILATION */
#define UNDER_TEST
#define CONFIG_stopHere()  do{ ; }while(1)

/* APPLICATION CONFIGURATION */
#define JSON_KEY_MAX_LEN             10U
#define JSON_VAL_MAX_LEN             20U    
#define JSON_MAX_STR_LEN            100U
//COMANDER

/* SERVER DATA */
#define CONF_SERVER_HOST                "electricity-manager1.herokuapp.com"
#define CONF_SERVER_UPDATE_ROUTE        "/enddef"



#endif	/* CONFIG_H */

