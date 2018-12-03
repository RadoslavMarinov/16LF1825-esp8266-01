#include "config.h"
#include "main.h"
#include "main-primary.h"
#include "mcc_generated_files/mcc.h"
#include "modules/receiver/receiver.h"
#include "modules/transmitter/transmitter.h"
#include "modules/communicatior/communicator.h"
#include "modules/transmitter/transmitter-primary.h"
#include "modules/eeprom/eeprom.h"
#include "modules/timer/timer.h"
#include "modules/esp/esp.h"

/*
 *  TODO:
 * Dont forget to reset frame buffer when parsing and handling is done!
 * What will do with handleEvReset /communicator.c
 * 
 * 013DC
 */ 

void main(void)
{

    main_init();
    ESP_ENABLE();

    esp_reset(timer_getTicksFromMS(ESP_RESET_TIME_MS), onEspReset);

    
    while (1)
    {
        if(receiver_task()){
            continue;
        }
        if(communicator_task()){
            continue;
        }
        if(timer_task()){
            continue;
        }
//        if(SYSTEM_TIMER_getTicks() > timer_getTicksFromSeconds(650) && !once){
//            timer_start(timer_getTicksFromSeconds(10), enableEsp);
//            once = 1;
//           LED_RED_OFF(); 
//        }
    }
}

void main_init(void){
    SYSTEM_Initialize();
    gpio_init();
    timer_init();
 
    communicator_init(false, ESP_MODE_PIN() ? communicator_espModeAccessPoint : communicator_espModeStation);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
}

void gpio_init(void){
    
    SWITCH1_OFF();
    SWITCH2_OFF();
    LED_RED_OFF();
    LED_GREEN_OFF();
    ESP_RESET_ENABLE(); 
    ESP_DISABLE(); 
}

static void onEspReset(void){
    timer_start(timer_getTicksFromMS(ESP_RESET_MSG_TIME_MS) , start_communication);
}

static void start_communication(void){
    receiver_start();
    communicator_initEsp();
}

/**
 End of File
*/





















    // When using interrupts, you need to set the Global and Peripheral Interrupt Enable bits
    // Use the following macros to:

    // Enable the Global Interrupts
    //INTERRUPT_GlobalInterruptEnable();

    // Enable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptEnable();

    // Disable the Global Interrupts
    //INTERRUPT_GlobalInterruptDisable();

    // Disable the Peripheral Interrupts
    //INTERRUPT_PeripheralInterruptDisable();