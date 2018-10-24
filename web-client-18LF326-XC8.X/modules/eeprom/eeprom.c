#include "../../config.h"
#include "eeprom-primary.h"
#include "eeprom.h"
#include "../../mcc_generated_files/memory.h"

static Self eeprom_self;

__eeprom char wifi_ssid[EE_WIFI_SSID_MAX_LEN] = "esp_def_network";
__eeprom char wifi_pwd[EE_WIFI_SSID_MAX_LEN] = "esp_def_pwd";



void eeprom_writeWiFiSsid(char * ssid, uint16_t len){
#ifdef UNDER_TEST
    if(len >= EE_WIFI_SSID_MAX_LEN){
        __raiseErr(errTooLongWifiSsid);
        CONFIG_stopHere();
    }
#endif 
    eeprom_writeStr(ssid, len, EE_IDX_WIFI_SSID);
}

void eeprom_writeStr(char * data, uint16_t len, uint16_t offset){
    uint16_t idx;
    for(idx = 0; idx < len; idx++){
        eeprom_writeByte(offset + idx, data[idx]);
    }
    eeprom_writeByte(offset + idx, '\0');
}

void eeprom_writeByte(uint16_t eeIdx, uint8_t data){
    
    if(eeIdx >= EE_SIZE){
        __raiseErr(errWriteAtWrongAddr);
        #ifdef UNDER_TEST
        CONFIG_stopHere();
        #endif
        return;
    }
    DATAEE_WriteByte(__getAddr(eeIdx), data );
}


void eeprom_readStr(char * data, uint16_t len, uint16_t startIdx){ 
    uint16_t idx;
    for(idx = 0; idx < len; idx++){
        data[idx] = eeprom_readByte(startIdx + idx);
    }
}

uint8_t eeprom_readByte(uint16_t eeIdx){
    
    if( eeIdx >= EE_SIZE ){
        __raiseErr(errWriteAtWrongAddr);
        #ifdef UNDER_TEST
        CONFIG_stopHere();
        #endif
        return 255;
    } else {
        return DATAEE_ReadByte(__getAddr(eeIdx));
    }
}