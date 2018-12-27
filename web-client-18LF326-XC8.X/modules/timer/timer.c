
#include "../../config.h"
#include "timer-primary.h"
#include "timer.h"

static timer_Self timer_self;



uint8_t timer_task(void){

    uint8_t didSomeWork = false;
    uint16_t timer;
    for(timer = 0; (__timerCont >> timer) > 0; timer++) {
        if(__isEnabledTimer(timer) && __hasExpiredTimer(timer)){
            if( __getTimerCb(timer) != NULL ){
                __runTimerCb(timer);
                timer_stop(timer);
                didSomeWork = true;
            } else {
                __setError(errCallBackNULL);
                CONF_raiseNvErrBit(conf_nvErr_timer_callBackNULL);
            }
        }
    }
    return didSomeWork;
} 

void timer_init(void){
    volatile int a;
    a = 0;
    uint16_t timer;
    // Trick the fucking compiler
    if(a){
        __setTimerCb(timer, timer_init);
    }
    // Disable all timers
    for(timer = 0; timer < TIMER_COUNT; timer++) {
        __setTimerCb(timer, NULL);
    }
    __timerCont = 0;
}

timer_Hook timer_start(Timner_Ticks after, Timer_CallBack cb){
    timer_Hook timer;
    for(timer = 0; timer < TIMER_COUNT; timer++) {
        if(!__isEnabledTimer(timer)){
            runTimer(timer, after, cb);
            return timer; 
        }
    }
#ifdef UNDER_TEST
    __setError(errTimerFull);
    CONFIG_stopHere();
#endif
    return -1;
}

//timer_Hook timer_startReapeatMode(Timner_Ticks after, Timer_CallBack eachCycleCb, uint16_t repeat,  timer_RepeatEndCallBack endCb){
//
//    return 15;
//    
//}


int8_t timer_stop(timer_Hook timer){
    if(__isEnabledTimer(timer)){
        __setTimerCb(timer, NULL);
        __disableTimer(timer);
        return 1;
    }
    return -1;
}

//timer_Code timer_restart(timer_Hook timer){
//    if(!__isEnabledTimer(timer)){
//        #ifdef UNDER_TEST
//        __setError(errTryingToRestartDisabledTimer);
//        CONFIG_stopHere();
//        #endif
//        return timer_codeNotEnabled;
//    } else {
//        runTimer(timer, __getTimerExpTime(timer), __getTimerCb(timer));
//        return timer_codeSuccess;
//    }
//}


static void runTimer(uint16_t timer, Timner_Ticks after, Timer_CallBack cb){
    __setTimerCb(timer, cb);
    __setTimerStartTime(timer, SYSTEM_TIMER_getTicks());
    __setTimerExpTime(timer, after);
    __enableTimer(timer);
}