#include "../../config.h"
#include "parser-primary.h"
#include "../receiver/receiver.h"
#include "parser.h"
#include "string.h"

Self parser_self;

void parser_init(Parser_OnMsg onMsgCb) {
    __onMsgCb = onMsgCb;
}

Parser_Codes parser_analyse(uint8_t * data, uint16_t len) {
    uint16_t lasFrStIdx = (len-1);
    
    Parser_Codes code = 0;
    do{
        lasFrStIdx--;
    } while(data[lasFrStIdx] != '\0' );
    lasFrStIdx++;
    /* Wait Message terminator "ERROR" | "OK" | "ready" */    
    if( strcmp((char *)&data[lasFrStIdx], "OK") == 0 ){
        code = parserCode_Ok;
    } else if(strcmp((char *)&data[lasFrStIdx], "ERROR") == 0 ){
        code = parserCode_Error;
    } else if(strcmp((char *)&data[lasFrStIdx], "ready") == 0 ){
        code = parserCode_Ready;
    } else {
        return parserCode_Unknown;
    }
    return code;
}