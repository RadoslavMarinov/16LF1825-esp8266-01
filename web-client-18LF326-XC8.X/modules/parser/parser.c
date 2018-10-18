#include "../../config.h"
#include "parser-primary.h"
#include "../receiver/receiver.h"
#include "parser.h"
#include "string.h"



uint8_t parser_analyse(uint8_t * data, uint16_t len) {
    uint16_t lasFrStIdx = (len-1) ;
    uint8_t code = 0;
    do{
        lasFrStIdx--;
    } while(data[lasFrStIdx] != '\0' );
    lasFrStIdx++;
    /* Wait Message terminator "ERROR" | "OK" | "ready" */    
    if( strcmp((char *)&data[lasFrStIdx], "OK") == 0 ){
        code = 0;
    } else if(strcmp((char *)&data[lasFrStIdx], "ERROR") == 0 ){
        code = 1;
    } else if(strcmp((char *)&data[lasFrStIdx], "ready") == 0 ){
        code = 254;
    } else {
        return PARSER_RC_PARSE_msgNotCompl;
    }
    return PARSER_RC_PARSE_msgCompl;
}