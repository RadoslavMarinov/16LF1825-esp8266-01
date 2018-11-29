/* 
 * File:   eeprom-mng-primary.h
 * Author: Riko
 *
 * Created on October 21, 2018, 8:23 AM
 */

#ifndef EEPROM_MNG_PRIMARY_H
#define	EEPROM_MNG_PRIMARY_H

#include "eeprom.h"

#define MODULE_NAME eeprom

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif


/******************************************************************************* 
 * CONFIGURATION
 ******************************************************************************/
#define EE_SIZE                     256U
#define EE_ADDR_OFFSET              0x7000U 
/******************************************************************************* 
 * CONFIGURATION
 ******************************************************************************/
#define EE_IDX_WIFI_PWD             0U
#define EE_WIFI_PWD_MAX_LEN        16U

#define EE_IDX_WIFI_SSID             ( EE_IDX_WIFI_PWD + EE_WIFI_PWD_MAX_LEN )
#define EE_WIFI_SSID_MAX_LEN        16U


/******************************************************************************* 
 * EEPROM LAYOUT 
 ******************************************************************************/


#define __getAddr(offset)            (EE_ADDR_OFFSET + (offset))
//#define __writeByte()  

/******************************************************************************* 
 * TYPEDEFS
 ******************************************************************************/
typedef struct {
    unsigned int errWriteAtWrongAddr;
    unsigned int errReadAtWrongAddr;
    unsigned int errTooLongWifiSsid;
}Errors;

typedef struct {
    Errors errors;
}Self;

/******************************************************************************* 
 * ERRORS
 ******************************************************************************/
#define __errors        (eeprom_self.errors)
#define __raiseErr(err)   do{ __errors.err  = 1; __addGlobalError();}while(0)
#define __clearErr(err)   do{ __errors.err  = 0; }while(0)

#endif	/* EEPROM_MNG_PRIMARY_H */

