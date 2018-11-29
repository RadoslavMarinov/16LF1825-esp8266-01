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

// 
#include "mcc_generated_files/tmr1.h"
#include "mcc_generated_files/pin_manager.h"

/* CONDITIONAL COMPILATION */
#define UNDER_TEST
#define CONFIG_stopHere()  do{ ; }while(1)

/* APPLICATION CONFIGURATION */
#define JSON_KEY_MAX_LEN             10U
#define JSON_VAL_MAX_LEN             20U    
#define JSON_MAX_STR_LEN            100U
//COMANDER

/*********************************** Interfaces ***********************************/
// Main
//The time taken to hold the ESP  in reset (viaRESET_PIN low)
#define ESP_RESET_TIME_MS           (500U)
/*
 *  After released from reset, a long message is being sent from ESP.
 * That message causes receiver frame buffer overflow. To prevent 
 * the overflow, this timeout is set to wait part of the message to
 * pass. Not the entire message should pass because the receiver detects
 * "ready" message to run the state machine. So this time should not be greater
 * than the ESP initialization message time, nor it should be too short 
 * because frame buffer overflows. 
 * During this time the recever is stopped and part of the message is thus ignored.
 */
#define ESP_RESET_MSG_TIME_MS       (180U)

//Timer
#define Timner_Ticks                TimerTicks    
#define TIMER_COUNT                 5
#define SYSTEM_TIMER_getTicks()     ( timer1_getTicks() )
#define TICKS_FREQ                  100LU

// GPIO
#define SWITCH1_ON()                do{ SW1_SetHigh(); }while(0)
#define SWITCH1_OFF()               do{ SW1_SetLow(); }while(0)

#define SWITCH2_ON()                do{ SW2_SetHigh(); }while(0)
#define SWITCH2_OFF()               do{ SW1_SetLow(); }while(0)

#define LED_RED_ON()                do{ LED2_SetLow(); }while(0)
#define LED_RED_OFF()               do{ LED2_SetHigh(); }while(0)

#define LED_GREEN_ON()              do{ LED1_SetLow(); }while(0)
#define LED_GREEN_OFF()             do{ LED1_SetHigh(); }while(0)

#define ESP_RESET_ENABLE()          do{ CH_RESET_SetLow(); }while(0)
#define ESP_RESET_DISABLE()         do{ CH_RESET_SetHigh(); }while(0)

#define ESP_ENABLE()                do{ CH_PD_SetHigh(); }while(0)
#define ESP_DISABLE()               do{ CH_PD_SetLow(); }while(0)

/* SERVER DATA */
#define CONF_SERVER_HOST                "electricity-manager1.herokuapp.com"
#define CONF_SERVER_UPDATE_ROUTE        "/enddev"



#endif	/* CONFIG_H */

