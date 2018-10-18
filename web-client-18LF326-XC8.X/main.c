#include "config.h"
#include "main.h"
#include "mcc_generated_files/mcc.h"
#include "modules/receiver/receiver.h"
#include "modules/transmitter/transmitter.h"
#include "modules/communicatior/communicator.h"
#include "modules/transmitter/transmitter-primary.h"

uint8_t arr[] = "RikoooRik";

void main(void)
{
    main_init();
    uint16_t old = 0;
    
    
    transmitter_send(arr, sizeof(arr));

    while (1)
    {
        if(timer1_getTicks() - old > 50 ){
            LED_Toggle();
            old = timer1_getTicks();
        }
        receiver_task();
//        LED_SetHigh();
//        LED_SetLow();
        
        // Add your application code
    }
}

void main_init(void){
    SYSTEM_Initialize();
    receiver_init();
    transmitter_init(NULL);
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