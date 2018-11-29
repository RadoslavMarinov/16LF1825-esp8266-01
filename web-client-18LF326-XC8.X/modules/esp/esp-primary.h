/* 
 * File:   esp-primary.h
 * Author: Riko
 *
 * Created on 28 ??????? 2018, 20:18
 */

#ifndef ESP_PRIMARY_H
#define	ESP_PRIMARY_H

#define MODULE_NAME esp

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif

/******************************************************************************* 
 * TYPEDEFS
 ******************************************************************************/
typedef struct {
    unsigned int errUnavailableTimer:1;
    unsigned int errAfterResetCallBackNULL:1;
}Errors;

typedef struct {
    int16_t timer;
    void (*afterReset)(void);
    Errors errors;   
}esp_Self;

#define __raiseError(err)               do {  esp_self.errors.err = 1; __addGlobalError(); }while(0)
#define __clearError(err)               do {  esp_self.errors.err = 0;}while(0)

#define __afterReset                    (esp_self.afterReset)
#define __setAfterReset(cb)             do{ __afterReset = (cb); }while(0)
#define __callAfterReset()              do{ __afterReset(); }while(0)

#define __timer                         (esp_self.timer)
#define __setTimerNumber(timer)         do{__timer  = (timer);}while(0)


#endif	/* ESP_PRIMARY_H */

