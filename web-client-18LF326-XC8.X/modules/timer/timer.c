
#include "../../config.h"
#include "timer-primary.h"
#include "timer.h"

static timer_Self timer_self;



uint8_t timer_task(void){

    uint8_t didSomeWork = false;
    uint16_t timer;
    for(timer = 0; timer < TIMER_COUNT; timer++) {
        if(__isEnabledTimer(timer) && __hasExpiredTimer(timer)){
            if( __getTimerCb(timer) != NULL ){
                __runTimerCb(timer);
                timer_stop(timer);
                didSomeWork = true;
            } else {
                __setError(errCallBackNULL);
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
        __disableTimer(timer);
    }
}

int16_t timer_start(Timner_Ticks after, Timer_CallBack cb){
    int16_t timer;
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


int8_t timer_stop(uint16_t timer){
    if(__isEnabledTimer(timer)){
        __setTimerCb(timer, NULL);
        __disableTimer(timer);
        return 1;
    }
    return -1;
}

static void runTimer(uint16_t timer, Timner_Ticks after, Timer_CallBack cb){
    __setTimerCb(timer, cb);
    __setTimerStartTime(timer, SYSTEM_TIMER_getTicks());
    __setTimerExpTime(timer, after);
    __enableTimer(timer);
}