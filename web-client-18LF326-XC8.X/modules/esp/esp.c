
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

void esp_reset(Timner_Ticks ticks, void(*cb)(void)) {
    int16_t timer = timer_start(ticks, releaseEspFromReset);
    if( timer < 0 ){
        __raiseError(errUnavailableTimer);
    } else {
        __setAfterReset(cb);
        __setTimerNumber(timer);
        ESP_RESET_ENABLE();
//        receiver_stop();
//        receiver_resetCircBuff();
//        receiver_resetFrBuff();
    }
}