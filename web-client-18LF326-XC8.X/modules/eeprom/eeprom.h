/* 
 * File:   eeprom-mng.h
 * Author: Riko
 *
 * Created on October 21, 2018, 8:22 AM
 */

#ifndef EEPROM_MNG_H
#define	EEPROM_MNG_H

typedef void (Eeprom_writeWiFiSsid_fp)(char * ssid, uint16_t len);
void eeprom_writeWiFiSsid(char * ssid, uint16_t len);

void eeprom_writeStr(char * data, uint16_t len, uint16_t offset);
void eeprom_readStr(char * data, uint16_t len, uint16_t eeIdx);
uint8_t eeprom_readByte(uint16_t eeIdx);
void eeprom_writeByte(uint16_t eeIdx, uint8_t data);

#endif	/* EEPROM_MNG_H */

