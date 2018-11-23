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
void eeprom_writeWiFiPwd(void* data);

void eeprom_writeStr(char * data, uint16_t offset);
char * eeprom_readStr(char * dest, uint16_t eeStartIdx);
uint8_t eeprom_readByte(uint16_t eeIdx);
void eeprom_writeByte(uint16_t eeIdx, uint8_t data);



char * eeprom_readWifiSsid(char * dest);
char * eeprom_readWifiPwd(char * dest);

#endif	/* EEPROM_MNG_H */

