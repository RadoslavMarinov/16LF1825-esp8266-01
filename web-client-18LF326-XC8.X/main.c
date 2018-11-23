#include "config.h"
#include "main.h"
#include "mcc_generated_files/mcc.h"
#include "modules/receiver/receiver.h"
#include "modules/transmitter/transmitter.h"
#include "modules/communicatior/communicator.h"
#include "modules/transmitter/transmitter-primary.h"
#include "modules/eeprom/eeprom.h"



//const uint8_t name[] = "RikoSonqRikoSonq";
//uint8_t nameR[30] ;

//void main_setLed(void * data){
//    uint16_t level;
//    level = *((uint16_t *)data);
//    if(level){
//        LED_SetHigh();
//    } else {
//        LED_SetLow();
//    }
//}
//__eeprom char regNumber[10] = "A93213";

void main(void)
{
    uint16_t old = 0;
    main_init();

    char c;
    
//    eeprom_writeStr((char*)name, 0x0);
//    eeprom_readStr((char*)nameR, 0x0);
//    c = eeprom_readByte(0x10);
    while (1)
    {
        if(receiver_task()){
            continue;
        }
        if(communicator_task()){
            continue;
        }
//        LED_Toggle();
         if(timer1_getTicks() - old > 50 ){
            LED_Toggle();
            old = timer1_getTicks();
        }
    }
}

void main_init(void){
    SYSTEM_Initialize();
//    receiver_init();
//    transmitter_init(NULL);
    communicator_init(true);
    INTERRUPT_GlobalInterruptEnable();
    INTERRUPT_PeripheralInterruptEnable();
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