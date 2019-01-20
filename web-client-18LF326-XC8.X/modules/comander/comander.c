
#include "../../config.h"
#include "comander.h"
#include "comander-primary.h"
#include "../eeprom/eeprom.h"
#include "../endpoints/binary-switch/binary-switch.h"

const Commander_commandMap commandMap = { .commander_commands={
    {"bs1s", binarySwitch_setInst1Level},             //binary switch 1 set value depend on the argument                      
    {"bs2s", binarySwitch_setInst2Level},             //binary switch 2 set value depend on the argument                     
    {"swfid", eeprom_writeWiFiSsid},        
    {"swfpwd", eeprom_writeWiFiPwd},                          
    {"z22", NULL},                         
} };

commander_Code commander_execute(char *command, void * value) {
    int16_t mapIdx;
    mapIdx = commander_find(command);
    
    /* If mapIdx is lower than 0 the string is not found.
     * If the callback at the corresponding unit index is NULL,
     * then there is no action to perform for the given command.
     */
    
    if( mapIdx >=0 ){
        if(__getCallBack(mapIdx) == NULL){
            CONF_raiseNvErrBit(conf_nvErr_commander_callBackNull);
            return commander_codeCallBackNull;
        }
        __runMapCallBack(mapIdx, value);
        return commander_codeOk;
    } else {
        CONF_raiseNvErrBit(conf_nvErr_commander_commandNotFound);
        return commander_codeCommandNotFound; 
    }
}                                                                                                                                     
/* Returns the index of the string(the command) if it is found.
 * If not found, returns -1.
 */
static int16_t commander_find(char *command) {
    uint16_t top,  bott, workTop, workBott, work;
    uint8_t charOffs = 0;
    uint8_t charFound = true;
//    uint8_t commIdx
    top = COMMANDER_COMMAND_COUNT - 1;
    bott = 0;

    while(top != bott && charFound ) {
        //    -- FIND TOP
        workTop = top;
        workBott = bott;

        while( workTop - workBott > 1 ) {
            work = (workTop + workBott) / 2;
            if( __getMapChar(work, charOffs)  > command[charOffs]) {
                workTop = work;
            } else {
                workBott = work;
            }
        }

        if( __getMapChar(workTop, charOffs) == command[charOffs] ){
            top = workTop;
        } else if( __getMapChar(workBott, charOffs) == command[charOffs] ){
            top = workBott;
        } else {
            charFound = false;
        } 
        //-- END FIND TOP
        
        //    -- FIND BOTT
        workTop = top;
        workBott = bott;

        while( workTop - workBott > 1 ){
            work = (workTop + workBott) / 2;
            if(  __getMapChar(work, charOffs) < command[charOffs] ){
                workBott = work;
            } else {
                workTop = work;
            }
        }

        if( __getMapChar(workBott, charOffs) == command[charOffs] ){
            bott = workBott;
        } else if( __getMapChar(workTop, charOffs) == command[charOffs] ){
            bott = workTop;
        } else {
            charFound = false;
        } 
        
        //-- END FIND BOTT
        charOffs++;
        
    }
    if( top == bott && charFound ) {
        if(strcmp(&__getMapChar(workTop, charOffs), &command[charOffs]) == 0 ){
            return top;
        } 
        return -1;
    } else {
        return -1;
    }
}

//uint16_t find_top(uint16_t top, uint16_t bott, char c, uint8_t offset){
//    uint16_t work;
//    
//    work = (top + bott) / 2;
//    
//    
//    
//}