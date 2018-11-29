/* 
 * File:   timer-primary.h
 * Author: Riko
 *
 * Created on 25 ??????? 2018, 17:03
 */

#ifndef TIMER_PRIMARY_H
#define	TIMER_PRIMARY_H

#include "../../config.h"
#include "timer.h"


#define MODULE_NAME timer

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif

/***************************************************
 Required interfaces
 **************************************************/



/***************************************************
 * Private typedefs
 **************************************************/

typedef struct {
  
    unsigned int errCallBackNULL :1;
    unsigned int errTimerFull :1;
    
}Errors;

typedef struct {
    Timner_Ticks expTicks;
    Timner_Ticks startTics;
    Timer_CallBack callBack;
    unsigned int on :1;
}Timer;
typedef struct {
    Errors errors;
    Timer timers[TIMER_COUNT];
}timer_Self;



/***************************************************
 
 **************************************************/
#define __timers                          (timer_self.timers)

//ERRORS
#define __errors                           (timer_self.errors)
#define __setError(err)                     do{ __errors.err = 1; __addGlobalError();}while(0)
#define __isRaisedError(err)                (__errors.err == 1 ? true : false )

// Expiration Time in Ticks
#define __setTimerExpTime(timer, time)    do{ __timers[timer].expTicks = (time); }while(0)
#define __getTimerExpTime(timer)          (__timers[timer].expTicks)
// Start Time Stamp in Ticks
#define __setTimerStartTime(timer, time)  do{ __timers[timer].startTics = (time); }while(0)
#define __getTimerStartTime(timer)          (__timers[timer].startTics)
// Call Back Function
#define __setTimerCb(timer, cb)           do{ __timers[timer].callBack = (cb); }while(0)
#define __getTimerCb(timer)               (__timers[timer].callBack)
#define __runTimerCb(timer)               do{ __timers[timer].callBack(); }while(0)
// Timer enable disable
#define __enableTimer(timer)              do{ __timers[timer].on = true; }while(0)
#define __isEnabledTimer(timer)           (__timers[timer].on)
#define __disableTimer(timer)              do{ __timers[timer].on = false; }while(0)


// OTHERS
#define __getExpiredTime(timer)           (SYSTEM_TIMER_getTicks() - __getTimerStartTime(timer))
#define __hasExpiredTimer(timer)          (__getExpiredTime(timer) >= __getTimerExpTime(timer) ?  true : false )

/***************************************************
 Private Function Declaration
 **************************************************/
static void runTimer(uint16_t timer, Timner_Ticks after, Timer_CallBack cb);

#endif	/* TIMER_PRIMARY_H */

