
#include "../../config.h"
#include "esp-primary.h"
#include "esp.h"
#include "../timer/timer.h"
#include "../receiver/receiver.h"

static esp_Self esp_self;

static void releaseEspFromReset(void){
    ESP_RESET_DISABLE();
    if(__afterReset != NULL){
        __callAfterReset();
        __afterReset = NULL;
    } else {
//        __raiseError(errAfterResetCallBackNULL);
    }
}


/*
 * Description: 
 *      Holds the enable-pin in disable state for time specified bu "ticks" parameter. 
 * Params:Disables ESP module by changing enable-Pin state.
 *      cb: callback function to be called when reset time expire.
 *      ticks: how much time in system ticks to hold the eps-enable pin in disable state.
 */
void esp_reset(void(*cb)(void)) {
    int16_t timer = timer_start(timer_getTicksFromMS(ESP_RESET_TIME_MS), releaseEspFromReset);
    if( timer < 0 ){
        __raiseError(errUnavailableTimer);
        CONF_raiseNvErrBit(conf_nvErr_esp_timerNotAvail);
    } else {
        __setAfterReset(cb);
        __setTimerNumber(timer);
        ESP_RESET_ENABLE();
//        receiver_stop();
//        receiver_resetFrBuff();
    }
}