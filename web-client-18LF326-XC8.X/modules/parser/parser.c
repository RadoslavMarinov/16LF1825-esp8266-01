#include "../../config.h"
#include "parser-primary.h"
#include "../receiver/receiver.h"
#include "parser.h"
#include "string.h"
#include "json-parser/json-parser.h"


/* Detects if frame is terminat*/
Parser_Codes parser_analyse(char * frameStAddr, uint16_t len) {

    char * curr = (char *)( frameStAddr + (len - 1) ); /*  "curr"should point to '\0'
                                                  * which is the end of the string/frame
                                                  */  
    uint8_t ch;
    
    Parser_Codes code = 0;
    
    curr = getStartOfStr(curr, len);
    
    /* Wait Message terminator "ERROR" | "OK" | "ready" */    
    if( strcmp(curr, "OK") == 0 ){
        code = parserCode_Ok;
    } else if(strcmp(curr, "JSON") == 0 ){      
        code = parserCode_Json;        
    } else if(strcmp(curr, "ERROR") == 0 ){
        code = parserCode_Error;
    } else if(strcmp(curr, "ready") == 0 ){
        code = parserCode_Ready;
    } else {
        return parserCode_Unknown;
    }
    return code;
}

uint8_t parser_substring(const char * subStr, const char * superStr){

	char * sup;
	char * csupr;
	char * sub;

	sup  = (char*)superStr;
	sub = (char*)subStr;

	while(*sup != '\0'){
		csupr = sup;
		while(*sub == *csupr && *sub != '\0'){
			sub++;
			csupr++;
		}

		if(*sub == '\0'){
			return true;
		} else {
			sup++;
			sub = (char*)subStr;
		}
	}

    return false;
}
/* "endCh is assumed to point to the end of string or the '\0' character"*/
static char * getStartOfStr(char * endCh, uint16_t len){
    int16_t length;
    char * ch;
    length = len;
    ch = endCh;
    do{
        ch--;
        length--;
    } while(*ch != '\0' && length > 0 );
    return ++ch;
}