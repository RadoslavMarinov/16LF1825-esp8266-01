#include "../../config.h"
#include "parser-primary.h"
#include "../receiver/receiver.h"
#include "parser.h"
#include "string.h"
#include "json-parser/json-parser.h"


/* Detects if frame is terminat*/
Parser_Codes parser_analyse(uint8_t * data, uint16_t len) {
    int16_t lasFrStIdx = (len-1);
    uint8_t ch;
    
    Parser_Codes code = 0;
    
    do{
        lasFrStIdx--;
        ch = data[lasFrStIdx];
    } while(data[lasFrStIdx] != '\0' && lasFrStIdx > -1 );
    
    lasFrStIdx++;
    
    /* Wait Message terminator "ERROR" | "OK" | "ready" */    
    if( strcmp((char *)&data[lasFrStIdx], "OK") == 0 ){
        code = parserCode_Ok;
    } else if(strcmp((char *)&data[lasFrStIdx], "JSON") == 0 ){      
        code = parserCode_Json;        
    } else if(strcmp((char *)&data[lasFrStIdx], "ERROR") == 0 ){
        code = parserCode_Error;
    } else if(strcmp((char *)&data[lasFrStIdx], "ready") == 0 ){
        code = parserCode_Ready;
    } else {
        return parserCode_Unknown;
    }
    return code;
}

uint8_t parser_substring(const char * subStr, const char * superStr){

	char * super;
	char * sub;

	super  = (char*)superStr;
	sub = (char*)subStr;

    while( *super != '\0'){
        while(*sub != *super && *super != '\0'){
            super++;
        }
        while(*sub == *super && *sub != '\0'){
            sub++;
            super++;
        }
        if(*sub == '\0'){
            return true;
        }
        sub = (char*)subStr;
    }
    return false;

}