/* 
 * File:   eeprom-mng.h
 * Author: Riko
 *
 * Created on October 21, 2018, 8:22 AM
 */

#ifndef EEPROM_MNG_H
#define	EEPROM_MNG_H

typedef void (Eeprom_writeWiFiSsid_fp)(char * ssid, uint16_t len);

void eeprom_writeWiFiSsid(void * data);
char * eeprom_readWifiSsid(char * dest);

void eeprom_writeWiFiPwd(void* data);
char * eeprom_readWifiPwd(char * dest);

void eeprom_writeNextError(char * error);
void eeprom_clearAllErrors(void);
void eeprom_raiseBit(uint16_t eeIdx, uint8_t eeBit);

void eeprom_writeStr(char * data, uint16_t offset);
char * eeprom_readStr(char * dest, uint16_t eeStartIdx);
void eeprom_readMem(uint16_t eeIdx, uint8_t * dest, uint16_t size);
uint8_t eeprom_readByte(uint16_t eeIdx);
void eeprom_writeByte(uint16_t eeIdx, uint8_t data);
void eeprom_erase(uint16_t from, uint16_t to);
void eeprom_memset(uint16_t from, uint16_t to, uint8_t data);

//Helpers
int16_t eeprom_findFirstOcurenceOf(uint16_t start, char ch);





#endif	/* EEPROM_MNG_H */

