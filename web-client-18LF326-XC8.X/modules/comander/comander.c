
#include "../../config.h"
#include "../eeprom/eeprom.h"
#include "comander.h"
#include "comander-primary.h"

const Commander_commandMap commandMap = { .commander_commands={
    {"a1", NULL},                           //0
    {"a2", NULL},                           
    {"b1", NULL},                           
    {"b11", NULL},
    {"c1", NULL},
    {"c12", NULL},                          //5
    {"swfid", eeprom_writeWiFiSsid},        
    {"swfpwd", NULL},                          
    {"z22", NULL},
    {"z22", NULL},                          //9  
} };

uint8_t commander_execute(char *command, void * value) {
    int16_t mapIdx;
    mapIdx = commander_find(command);
    if( mapIdx >=0 && __getCallBack(mapIdx) != NULL ){
        __runMapCallBack(mapIdx, value);
    } else {
        return 1;
    }
    
    return 0;
}

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