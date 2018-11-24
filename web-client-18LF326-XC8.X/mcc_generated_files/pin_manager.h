/**
  @Generated Pin Manager Header File

  @Company:
    Microchip Technology Inc.

  @File Name:
    pin_manager.h

  @Summary:
    This is the Pin Manager file generated using PIC10 / PIC12 / PIC16 / PIC18 MCUs

  @Description
    This header file provides APIs for driver for .
    Generation Information :
        Product Revision  :  PIC10 / PIC12 / PIC16 / PIC18 MCUs - 1.65.2
        Device            :  PIC16LF18326
        Driver Version    :  2.11
    The generated drivers are tested against the following:
        Compiler          :  XC8 1.45
        MPLAB 	          :  MPLAB X 4.15	
*/

/*
    (c) 2018 Microchip Technology Inc. and its subsidiaries. 
    
    Subject to your compliance with these terms, you may use Microchip software and any 
    derivatives exclusively with Microchip products. It is your responsibility to comply with third party 
    license terms applicable to your use of third party software (including open source software) that 
    may accompany Microchip software.
    
    THIS SOFTWARE IS SUPPLIED BY MICROCHIP "AS IS". NO WARRANTIES, WHETHER 
    EXPRESS, IMPLIED OR STATUTORY, APPLY TO THIS SOFTWARE, INCLUDING ANY 
    IMPLIED WARRANTIES OF NON-INFRINGEMENT, MERCHANTABILITY, AND FITNESS 
    FOR A PARTICULAR PURPOSE.
    
    IN NO EVENT WILL MICROCHIP BE LIABLE FOR ANY INDIRECT, SPECIAL, PUNITIVE, 
    INCIDENTAL OR CONSEQUENTIAL LOSS, DAMAGE, COST OR EXPENSE OF ANY KIND 
    WHATSOEVER RELATED TO THE SOFTWARE, HOWEVER CAUSED, EVEN IF MICROCHIP 
    HAS BEEN ADVISED OF THE POSSIBILITY OR THE DAMAGES ARE FORESEEABLE. TO 
    THE FULLEST EXTENT ALLOWED BY LAW, MICROCHIP'S TOTAL LIABILITY ON ALL 
    CLAIMS IN ANY WAY RELATED TO THIS SOFTWARE WILL NOT EXCEED THE AMOUNT 
    OF FEES, IF ANY, THAT YOU HAVE PAID DIRECTLY TO MICROCHIP FOR THIS 
    SOFTWARE.
*/

#ifndef PIN_MANAGER_H
#define PIN_MANAGER_H

#define INPUT   1
#define OUTPUT  0

#define HIGH    1
#define LOW     0

#define ANALOG      1
#define DIGITAL     0

#define PULL_UP_ENABLED      1
#define PULL_UP_DISABLED     0

// get/set SW1 aliases
#define SW1_TRIS                 TRISAbits.TRISA1
#define SW1_LAT                  LATAbits.LATA1
#define SW1_PORT                 PORTAbits.RA1
#define SW1_WPU                  WPUAbits.WPUA1
#define SW1_OD                   ODCONAbits.ODCA1
#define SW1_ANS                  ANSELAbits.ANSA1
#define SW1_SetHigh()            do { LATAbits.LATA1 = 1; } while(0)
#define SW1_SetLow()             do { LATAbits.LATA1 = 0; } while(0)
#define SW1_Toggle()             do { LATAbits.LATA1 = ~LATAbits.LATA1; } while(0)
#define SW1_GetValue()           PORTAbits.RA1
#define SW1_SetDigitalInput()    do { TRISAbits.TRISA1 = 1; } while(0)
#define SW1_SetDigitalOutput()   do { TRISAbits.TRISA1 = 0; } while(0)
#define SW1_SetPullup()          do { WPUAbits.WPUA1 = 1; } while(0)
#define SW1_ResetPullup()        do { WPUAbits.WPUA1 = 0; } while(0)
#define SW1_SetPushPull()        do { ODCONAbits.ODCA1 = 0; } while(0)
#define SW1_SetOpenDrain()       do { ODCONAbits.ODCA1 = 1; } while(0)
#define SW1_SetAnalogMode()      do { ANSELAbits.ANSA1 = 1; } while(0)
#define SW1_SetDigitalMode()     do { ANSELAbits.ANSA1 = 0; } while(0)

// get/set SW2 aliases
#define SW2_TRIS                 TRISAbits.TRISA2
#define SW2_LAT                  LATAbits.LATA2
#define SW2_PORT                 PORTAbits.RA2
#define SW2_WPU                  WPUAbits.WPUA2
#define SW2_OD                   ODCONAbits.ODCA2
#define SW2_ANS                  ANSELAbits.ANSA2
#define SW2_SetHigh()            do { LATAbits.LATA2 = 1; } while(0)
#define SW2_SetLow()             do { LATAbits.LATA2 = 0; } while(0)
#define SW2_Toggle()             do { LATAbits.LATA2 = ~LATAbits.LATA2; } while(0)
#define SW2_GetValue()           PORTAbits.RA2
#define SW2_SetDigitalInput()    do { TRISAbits.TRISA2 = 1; } while(0)
#define SW2_SetDigitalOutput()   do { TRISAbits.TRISA2 = 0; } while(0)
#define SW2_SetPullup()          do { WPUAbits.WPUA2 = 1; } while(0)
#define SW2_ResetPullup()        do { WPUAbits.WPUA2 = 0; } while(0)
#define SW2_SetPushPull()        do { ODCONAbits.ODCA2 = 0; } while(0)
#define SW2_SetOpenDrain()       do { ODCONAbits.ODCA2 = 1; } while(0)
#define SW2_SetAnalogMode()      do { ANSELAbits.ANSA2 = 1; } while(0)
#define SW2_SetDigitalMode()     do { ANSELAbits.ANSA2 = 0; } while(0)

// get/set LED1 aliases
#define LED1_TRIS                 TRISCbits.TRISC0
#define LED1_LAT                  LATCbits.LATC0
#define LED1_PORT                 PORTCbits.RC0
#define LED1_WPU                  WPUCbits.WPUC0
#define LED1_OD                   ODCONCbits.ODCC0
#define LED1_ANS                  ANSELCbits.ANSC0
#define LED1_SetHigh()            do { LATCbits.LATC0 = 1; } while(0)
#define LED1_SetLow()             do { LATCbits.LATC0 = 0; } while(0)
#define LED1_Toggle()             do { LATCbits.LATC0 = ~LATCbits.LATC0; } while(0)
#define LED1_GetValue()           PORTCbits.RC0
#define LED1_SetDigitalInput()    do { TRISCbits.TRISC0 = 1; } while(0)
#define LED1_SetDigitalOutput()   do { TRISCbits.TRISC0 = 0; } while(0)
#define LED1_SetPullup()          do { WPUCbits.WPUC0 = 1; } while(0)
#define LED1_ResetPullup()        do { WPUCbits.WPUC0 = 0; } while(0)
#define LED1_SetPushPull()        do { ODCONCbits.ODCC0 = 0; } while(0)
#define LED1_SetOpenDrain()       do { ODCONCbits.ODCC0 = 1; } while(0)
#define LED1_SetAnalogMode()      do { ANSELCbits.ANSC0 = 1; } while(0)
#define LED1_SetDigitalMode()     do { ANSELCbits.ANSC0 = 0; } while(0)

// get/set LED2 aliases
#define LED2_TRIS                 TRISCbits.TRISC1
#define LED2_LAT                  LATCbits.LATC1
#define LED2_PORT                 PORTCbits.RC1
#define LED2_WPU                  WPUCbits.WPUC1
#define LED2_OD                   ODCONCbits.ODCC1
#define LED2_ANS                  ANSELCbits.ANSC1
#define LED2_SetHigh()            do { LATCbits.LATC1 = 1; } while(0)
#define LED2_SetLow()             do { LATCbits.LATC1 = 0; } while(0)
#define LED2_Toggle()             do { LATCbits.LATC1 = ~LATCbits.LATC1; } while(0)
#define LED2_GetValue()           PORTCbits.RC1
#define LED2_SetDigitalInput()    do { TRISCbits.TRISC1 = 1; } while(0)
#define LED2_SetDigitalOutput()   do { TRISCbits.TRISC1 = 0; } while(0)
#define LED2_SetPullup()          do { WPUCbits.WPUC1 = 1; } while(0)
#define LED2_ResetPullup()        do { WPUCbits.WPUC1 = 0; } while(0)
#define LED2_SetPushPull()        do { ODCONCbits.ODCC1 = 0; } while(0)
#define LED2_SetOpenDrain()       do { ODCONCbits.ODCC1 = 1; } while(0)
#define LED2_SetAnalogMode()      do { ANSELCbits.ANSC1 = 1; } while(0)
#define LED2_SetDigitalMode()     do { ANSELCbits.ANSC1 = 0; } while(0)

// get/set CH_RESET aliases
#define CH_RESET_TRIS                 TRISCbits.TRISC2
#define CH_RESET_LAT                  LATCbits.LATC2
#define CH_RESET_PORT                 PORTCbits.RC2
#define CH_RESET_WPU                  WPUCbits.WPUC2
#define CH_RESET_OD                   ODCONCbits.ODCC2
#define CH_RESET_ANS                  ANSELCbits.ANSC2
#define CH_RESET_SetHigh()            do { LATCbits.LATC2 = 1; } while(0)
#define CH_RESET_SetLow()             do { LATCbits.LATC2 = 0; } while(0)
#define CH_RESET_Toggle()             do { LATCbits.LATC2 = ~LATCbits.LATC2; } while(0)
#define CH_RESET_GetValue()           PORTCbits.RC2
#define CH_RESET_SetDigitalInput()    do { TRISCbits.TRISC2 = 1; } while(0)
#define CH_RESET_SetDigitalOutput()   do { TRISCbits.TRISC2 = 0; } while(0)
#define CH_RESET_SetPullup()          do { WPUCbits.WPUC2 = 1; } while(0)
#define CH_RESET_ResetPullup()        do { WPUCbits.WPUC2 = 0; } while(0)
#define CH_RESET_SetPushPull()        do { ODCONCbits.ODCC2 = 0; } while(0)
#define CH_RESET_SetOpenDrain()       do { ODCONCbits.ODCC2 = 1; } while(0)
#define CH_RESET_SetAnalogMode()      do { ANSELCbits.ANSC2 = 1; } while(0)
#define CH_RESET_SetDigitalMode()     do { ANSELCbits.ANSC2 = 0; } while(0)

// get/set CH_PD aliases
#define CH_PD_TRIS                 TRISCbits.TRISC3
#define CH_PD_LAT                  LATCbits.LATC3
#define CH_PD_PORT                 PORTCbits.RC3
#define CH_PD_WPU                  WPUCbits.WPUC3
#define CH_PD_OD                   ODCONCbits.ODCC3
#define CH_PD_ANS                  ANSELCbits.ANSC3
#define CH_PD_SetHigh()            do { LATCbits.LATC3 = 1; } while(0)
#define CH_PD_SetLow()             do { LATCbits.LATC3 = 0; } while(0)
#define CH_PD_Toggle()             do { LATCbits.LATC3 = ~LATCbits.LATC3; } while(0)
#define CH_PD_GetValue()           PORTCbits.RC3
#define CH_PD_SetDigitalInput()    do { TRISCbits.TRISC3 = 1; } while(0)
#define CH_PD_SetDigitalOutput()   do { TRISCbits.TRISC3 = 0; } while(0)
#define CH_PD_SetPullup()          do { WPUCbits.WPUC3 = 1; } while(0)
#define CH_PD_ResetPullup()        do { WPUCbits.WPUC3 = 0; } while(0)
#define CH_PD_SetPushPull()        do { ODCONCbits.ODCC3 = 0; } while(0)
#define CH_PD_SetOpenDrain()       do { ODCONCbits.ODCC3 = 1; } while(0)
#define CH_PD_SetAnalogMode()      do { ANSELCbits.ANSC3 = 1; } while(0)
#define CH_PD_SetDigitalMode()     do { ANSELCbits.ANSC3 = 0; } while(0)

// get/set RC4 procedures
#define RC4_SetHigh()            do { LATCbits.LATC4 = 1; } while(0)
#define RC4_SetLow()             do { LATCbits.LATC4 = 0; } while(0)
#define RC4_Toggle()             do { LATCbits.LATC4 = ~LATCbits.LATC4; } while(0)
#define RC4_GetValue()              PORTCbits.RC4
#define RC4_SetDigitalInput()    do { TRISCbits.TRISC4 = 1; } while(0)
#define RC4_SetDigitalOutput()   do { TRISCbits.TRISC4 = 0; } while(0)
#define RC4_SetPullup()             do { WPUCbits.WPUC4 = 1; } while(0)
#define RC4_ResetPullup()           do { WPUCbits.WPUC4 = 0; } while(0)
#define RC4_SetAnalogMode()         do { ANSELCbits.ANSC4 = 1; } while(0)
#define RC4_SetDigitalMode()        do { ANSELCbits.ANSC4 = 0; } while(0)

// get/set RC5 procedures
#define RC5_SetHigh()            do { LATCbits.LATC5 = 1; } while(0)
#define RC5_SetLow()             do { LATCbits.LATC5 = 0; } while(0)
#define RC5_Toggle()             do { LATCbits.LATC5 = ~LATCbits.LATC5; } while(0)
#define RC5_GetValue()              PORTCbits.RC5
#define RC5_SetDigitalInput()    do { TRISCbits.TRISC5 = 1; } while(0)
#define RC5_SetDigitalOutput()   do { TRISCbits.TRISC5 = 0; } while(0)
#define RC5_SetPullup()             do { WPUCbits.WPUC5 = 1; } while(0)
#define RC5_ResetPullup()           do { WPUCbits.WPUC5 = 0; } while(0)
#define RC5_SetAnalogMode()         do { ANSELCbits.ANSC5 = 1; } while(0)
#define RC5_SetDigitalMode()        do { ANSELCbits.ANSC5 = 0; } while(0)

/**
   @Param
    none
   @Returns
    none
   @Description
    GPIO and peripheral I/O initialization
   @Example
    PIN_MANAGER_Initialize();
 */
void PIN_MANAGER_Initialize (void);

/**
 * @Param
    none
 * @Returns
    none
 * @Description
    Interrupt on Change Handling routine
 * @Example
    PIN_MANAGER_IOC();
 */
void PIN_MANAGER_IOC(void);



#endif // PIN_MANAGER_H
/**
 End of File
*/