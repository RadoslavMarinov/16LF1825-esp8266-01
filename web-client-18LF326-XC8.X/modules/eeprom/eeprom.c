#include "../../config.h"
#include "eeprom-primary.h"
#include "eeprom.h"
#include "../../mcc_generated_files/memory.h"

static Self eeprom_self;

//__eeprom char wifi_ssid[EE_WIFI_SSID_MAX_LEN] = "riko_main";
//__eeprom char wifi_pwd[EE_WIFI_SSID_MAX_LEN] = "koinarci88";


/*******************************************************************************
 CALLBACKS USED FOR STRING GUNCTION MAP
 ******************************************************************************/
void eeprom_writeWiFiSsid(void* data){
#ifdef UNDER_TEST
    if(strlen(data) >= EE_WIFI_SSID_MAX_LEN){
        __raiseErr(errTooLongWifiSsid);
        CONFIG_stopHere();
    }
#endif 
    NOP();
    eeprom_writeStr(data, EE_IDX_WIFI_SSID);
}

void eeprom_writeWiFiPwd(void* data){
#ifdef UNDER_TEST
    if( strlen(data) >= EE_WIFI_PWD_MAX_LEN ){
        __raiseErr(errTooLongWifiSsid);
        CONFIG_stopHere();
    }
#endif 
   eeprom_writeStr(data, EE_IDX_WIFI_PWD); 
}


/******************************************************************************/





void eeprom_writeStr(char * data, uint16_t offset){
    uint16_t idx = 0;
    while(data[idx] != '\0'){
        
        eeprom_writeByte(offset + idx, data[idx]);
        idx++;
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


char * eeprom_readStr(char * dest, uint16_t eeStartIdx){ 
    uint16_t idx = 0;
    char ch;
    ch = eeprom_readByte(eeStartIdx + idx);
    while( ch != '\0'){
        dest[idx] = ch;
        idx++;
        ch = eeprom_readByte(eeStartIdx + idx);
    }
    dest[idx] = '\0';
    return dest;
}

uint8_t eeprom_readByte(uint16_t eeIdx){
    
    if( eeIdx >= EE_SIZE ){
        __raiseErr(errReadAtWrongAddr);
        #ifdef UNDER_TEST
        CONFIG_stopHere();
        #endif
        return 255;
    } else {
        return DATAEE_ReadByte(__getAddr(eeIdx));
    }
}

char * eeprom_readWifiSsid(char * dest){
    return eeprom_readStr(dest, EE_IDX_WIFI_SSID);
}

char * eeprom_readWifiPwd(char * dest) {
    return eeprom_readStr(dest, EE_IDX_WIFI_PWD);
}