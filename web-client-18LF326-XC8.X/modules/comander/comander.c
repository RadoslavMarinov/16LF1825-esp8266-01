
#include "../../config.h"
#include "../eeprom/eeprom.h"
#include "comander.h"
#include "comander-primary.h"


const Commander_commandMap commandMap = { .commander_commands={
    {"swfid", eeprom_writeWiFiSsid},
    {"swfpwd", NULL}
} };