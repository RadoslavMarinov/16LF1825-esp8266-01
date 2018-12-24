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

char * eeprom_readWifiSsid(char * dest){
    return eeprom_readStr(dest, EE_IDX_WIFI_SSID);
}

void eeprom_writeWiFiPwd(void* data){
#ifdef UNDER_TEST
    if( strlen(data) >= EE_WIFI_PWD_MAX_LEN ){
        __raiseErr(errTooLongWifiSsid);
        CONFIG_stopHere();
    }
#endif 
   config_dummyFunc();
   eeprom_writeStr(data, EE_IDX_WIFI_PWD);
}

char * eeprom_readWifiPwd(char * dest) {
    return eeprom_readStr(dest, EE_IDX_WIFI_PWD);
}

void eeprom_raiseBit(uint16_t eeIdx, uint8_t eeBit){
    uint8_t eeByte;
    eeByte = eeprom_readByte(eeIdx);
    if(eeByte & (1 << eeBit)){
        return; //Already raised!
    } else {
        
        eeByte |= (1 << eeBit);
        
        eeprom_writeByte(eeIdx, eeByte);
    }
    
}

//void eeprom_writeNextError(char * error){
//    int16_t nextErrEeIdx = EE_DIAG_ERRS;
//#ifdef UNDER_TEST
//    if(strlen(error) >= EE_DIAG_ERRS_LEN ){
//        CONFIG_stopHere();
//    }
//#endif
//    if(eeprom_readByte(EE_DIAG_ERRS) == 0xFF){
//        nextErrEeIdx = EE_DIAG_ERRS;
//    } else {
//        do{
//            nextErrEeIdx = eeprom_findFirstOcurenceOf(nextErrEeIdx, '\0');
//            if(nextErrEeIdx < 0 ){
//                //TODO - Put error here to signify eeprom error overflow
//                return;
//            } else {
//                nextErrEeIdx++;
//            }
//        }while(eeprom_readByte(nextErrEeIdx) != 0xFF);
//        
//    }
//    eeprom_writeStr(error, nextErrEeIdx);
//}

void eeprom_clearAllErrors(void){
    eeprom_memset(EE_DIAG_ERRS, EE_DIAG_ERRS_END, 0x00);
}


/******************************************************************************/

void eeprom_writeStr(char * data, uint16_t offset){
    while(*data != '\0'  && offset < EE_SIZE){
        
        eeprom_writeByte(offset, *data);
        offset++;
        data++;
    }
    eeprom_writeByte(offset, '\0');
}

void eeprom_writeByte(uint16_t eeIdx, uint8_t data){
    
    if(eeIdx >= EE_SIZE){
        __raiseErr(errWriteAtBeyondEepromAddrSpace);
        return;
    }
    DATAEE_WriteByte(__getAddr(eeIdx), data );
}

void eeprom_readMem(uint16_t eeIdx, uint8_t * dest, uint16_t size){
    uint16_t cur;
    uint8_t data;
    while( eeIdx < EE_SIZE && (size > 0) ){
        data = eeprom_readByte(eeIdx);
        *dest = data;
        dest++;
        size--;
        eeIdx++;
    }
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

/*
 * !!! NOT TESTED
 "from"  "to"  inclusive 
 */
void eeprom_erase(uint16_t from, uint16_t to){
    eeprom_memset(from, to, 0xFF);
}

void eeprom_memset(uint16_t from, uint16_t to, uint8_t data){
    uint16_t cur = from;
    if(cur >= EE_SIZE ){
        return;
    } else {
        do{
            eeprom_writeByte(cur, data);
            cur++;
        } while(cur <= to || cur < EE_SIZE);
    }
    
}



//int16_t eeprom_findFirstOcurenceOf(uint16_t start, char ch){
//    char cur;
//    int16_t eeIdx = start;
//    do{
//        if(eeIdx >= EE_SIZE){
//            return -1;
//        }
//        cur = eeprom_readByte(eeIdx);
//        eeIdx++;
//    }while(cur != ch);
//
//    return --eeIdx;
//       
//}