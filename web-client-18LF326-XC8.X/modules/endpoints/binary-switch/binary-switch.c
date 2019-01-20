#include "binary-switch-primary.h"

void binarySwitch_init(uint8_t sw1Lvl, uint8_t sw2Lvl){
    if(sw1Lvl){
       SWITCH1_ON();
    } else {
        SWITCH1_OFF();
    }
    // SW2
    if(sw2Lvl){
        SWITCH2_ON();
    }else {
        SWITCH2_OFF();
    }
}

void binarySwitch_setInst1Level(void * level){
    uint16_t lvl = (*((uint16_t*)level));
    if(lvl){
        SWITCH1_ON();
        eeprom_writeByte(EE_SW1_LEV_ADDR, 1);
    } else {
        SWITCH1_OFF();
        eeprom_writeByte(EE_SW1_LEV_ADDR, 0);
    }
}

void binarySwitch_setInst2Level(void * level){
    uint16_t lvl = (*((uint16_t*)level));
    if(lvl){
        SWITCH2_ON();
        eeprom_writeByte(EE_SW2_LEV_ADDR, 1);
    } else {
        SWITCH2_OFF();
        eeprom_writeByte(EE_SW2_LEV_ADDR, 0);
    }
}