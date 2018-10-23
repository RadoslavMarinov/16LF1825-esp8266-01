/* 
 * File:   eeprom-mng.h
 * Author: Riko
 *
 * Created on October 21, 2018, 8:22 AM
 */

#ifndef EEPROM_MNG_H
#define	EEPROM_MNG_H


void eeprom_writeData(uint8_t * data, uint16_t len, uint16_t offset);
void eeprom_readData(uint8_t * data, uint16_t len, uint16_t eeIdx);
uint8_t eeprom_readByte(uint16_t eeIdx);
void eeprom_writeByte(uint16_t eeIdx, uint8_t data);

#endif	/* EEPROM_MNG_H */

