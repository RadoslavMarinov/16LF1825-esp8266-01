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

#if (TIMER_COUNT > 16)
#error "TIMER_COUNT too big can not fit in timer_Container"
#endif

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
    unsigned int errTryingToRestartDisabledTimer :1;
    
}Errors;

typedef struct {
    Timner_Ticks expTicks;
    Timner_Ticks startTics;
    Timer_CallBack callBack;
    timer_RepeatEndCallBack repeatEndCb;
    uint16_t repeat;
}Timer;
typedef struct {
    timer_Container timerCont;
    Errors errors;
    Timer timers[TIMER_COUNT];
}timer_Self;



/***************************************************
 
 **************************************************/
#define __timers                          (timer_self.timers)

// TIMER CONTAINER - an optimized way to check whether there are more active timers
#define __timerCont                         (timer_self.timerCont)
#define __enableTimer(timer)                do{ __timerCont |= (1 << timer);}while(0)
#define __disableTimer(timer)               do{ __timerCont &= (~((timer_Container)1 << timer));}while(0)
#define __isEnabledTimer(timer)             ( __timerCont & (1 << timer) ? true : false )
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
// Call Back Function - every timeout this function is called
#define __setTimerCb(timer, cb)           do{ __timers[timer].callBack = (cb); }while(0)
#define __getTimerCb(timer)               (__timers[timer].callBack)
#define __runTimerCb(timer)               do{ __timers[timer].callBack(); }while(0)
// End of repeat callback - this function is called when all the rep. cycles expire
#define setRepeatEndCb(timer, rcb)       do{__timers[timer].repeatEndCb = (rcb);}while(0);
#define getRepeatEndCb(timer)               ( __timers[timer].repeatEndCb )
#define callRepeatEndCb(timer)              do{getRepeatEndCb(timer)(timer);}while(0)
// REPEAT -  set how many times the timer will recycle 
#define setRepeat(timer, rpt)               do{  __timers[timer].repeat = rpt; }while(0)
        // this is decremented automatically by timer_task
#define getRepeat(timer)                    ( __timers[timer].repeat )



// OTHERS
#define __getExpiredTime(timer)           (SYSTEM_TIMER_getTicks() - __getTimerStartTime(timer))
#define __hasExpiredTimer(timer)          (__getExpiredTime(timer) >= __getTimerExpTime(timer) ?  true : false )

/***************************************************
 Private Function Declaration
 **************************************************/
static void runTimer(uint16_t timer, Timner_Ticks after, Timer_CallBack cb);

#endif	/* TIMER_PRIMARY_H */

