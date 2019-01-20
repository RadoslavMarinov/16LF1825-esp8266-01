/* 
 * File:   binary-switch-primary.h
 * Author: Riko
 *
 * Created on 30 ???????? 2018, 16:26
 */

#ifndef BINARY_SWITCH_PRIMARY_H
#define	BINARY_SWITCH_PRIMARY_H

#include "../../../config.h"
#include "../../eeprom/eeprom.h"
#include "binary-switch.h"

#ifndef SWITCH1_ON
#error "Missing required SWITCH1_ON()"
#endif

#ifndef SWITCH1_OFF
#error "Missing required SWITCH1_OFF()"
#endif

#ifndef SWITCH2_ON
#error "Missing required SWITCH2_ON()"
#endif

#ifndef SWITCH2_OFF
#error "Missing required SWITCH2_OFF()"
#endif

#ifndef EE_SW1_LEV_ADDR
#error "Missing required EE_SW1_LEV_ADDR"
#endif

#ifndef EE_SW2_LEV_ADDR
#error "Missing required EE_SW2_LEV_ADDR"
#endif



#endif	/* BINARY_SWITCH_PRIMARY_H */

