/* 
 * File:   timer.h
 * Author: Riko
 *
 * Created on 25 ??????? 2018, 17:03
 */

#ifndef TIMER_H
#define	TIMER_H

#ifndef TICKS_FREQ
#error "Missing required TICKS_FREQ"
#endif

#define timer_getTicksFromSeconds(secs)   ( (secs) * TICKS_FREQ )
#define timer_getTicksFromMS(ms)          ( (ms) / ( 1000 / TICKS_FREQ ) )

typedef void (*Timer_CallBack)(void);

typedef uint16_t timer_Hook;
typedef enum {
    timer_codeSuccess,
    timer_codeNotEnabled,
}timer_Code;
uint8_t timer_task(void);

/*
 returns: 
 * index of the timer being ran
 * -1 if all timers are busy 
 */
timer_Hook timer_start(Timner_Ticks after, Timer_CallBack cb);

/*
 * returns: 
 * 1 if timer successfully stopped.
 * -1 if timer is already stopped or disabled 
 */
int8_t timer_stop(timer_Hook timer);

timer_Code timer_restart(timer_Hook timer);

void timer_init(void);
#endif	/* TIMER_H */

