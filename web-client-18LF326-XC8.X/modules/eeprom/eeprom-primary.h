/* 
 * File:   eeprom-mng-primary.h
 * Author: Riko
 *
 * Created on October 21, 2018, 8:23 AM
 */

#ifndef EEPROM_MNG_PRIMARY_H
#define	EEPROM_MNG_PRIMARY_H

#include "eeprom.h"


#ifndef EE_DIAG_ERRS // NV memory diagnostig errors start address
#error "Missing required EE_DIAG_ERRS"
#endif

#ifndef EE_DIAG_ERRS_LEN // NV memory diagnostig errors Length in bytes
#error "Missing required EE_DIAG_ERRS_LEN"
#endif

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
// SERVER SSID - START 0 end 15
#define EE_IDX_WIFI_SSID            0U    
#define EE_WIFI_SSID_MAX_LEN        16U
// SERVER SSID - START 16 end 31
#define EE_IDX_WIFI_PWD             ( EE_IDX_WIFI_SSID + EE_WIFI_SSID_MAX_LEN )
#define EE_WIFI_PWD_MAX_LEN         16U
// ERRORS - START 200 end 255

#define EE_DIAG_ERRS_END            (EE_DIAG_ERRS + (EE_DIAG_ERRS_LEN))
/******************************************************************************* 
 * EEPROM LAYOUT 
 ******************************************************************************/


#define __getAddr(offset)            (EE_ADDR_OFFSET + (offset))
//#define __writeByte()  

/******************************************************************************* 
 * TYPEDEFS
 ******************************************************************************/
typedef struct {
    unsigned int errWriteAtBeyondEepromAddrSpace;
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

