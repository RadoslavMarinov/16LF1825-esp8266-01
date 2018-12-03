#include "../../config.h"
#include "parser-primary.h"
#include "parser.h"
#include "../receiver/receiver.h"
#include "string.h"
#include "json-parser/json-parser.h"
#include "http-parser/http-parser.h"
#include "../utils/utils.h"


/* Detects if frame is terminat*/
Parser_Codes parser_analyse(char * frameStAddr, uint16_t len) {

    char * curr = (char *)( frameStAddr + (len - 1) ); /*  "curr"should point to '\0'
                                                  * which is the end of the string/frame
                                                  */  
    Parser_Codes code = parserCode_Unknown;
    
    curr = getStartOfStr(curr, len);
    
    /* Wait Message terminator "ERROR" | "OK" | "ready" */    
    if( strcmp(curr, "OK") == 0 ){
        code = parserCode_Ok;
    }  else if(strcmp(curr, "ERROR") == 0 ){
        code = parserCode_Error;
    } else if(strcmp(curr, "ready") == 0 ){
        code = parserCode_Ready;
    } else {
        return parserCode_Unknown;
    }
    return code;
}

Parser_Codes parser_httpServer(char * frameStAddr, uint16_t len) {
    char * cur = (char *)( frameStAddr + (len - 1) ); /*  "curr"should point to '\0'
                                                        * which is the end of the string/frame
                                                        */  
    char * substrStart = NULL;
    Parser_Codes code = parserCode_Unknown;
    httpParser_HttpHeader *httpHeader;
    cur = getStartOfStr(cur, len);
    

    if( strncmp("+IPD", cur, 4) == 0 ){
        cur += 4; // Skip "+IPD" and start after it.
        substrStart = utils_substring(":", cur);
        if(substrStart != NULL){
            
            cur = substrStart + 1; /*"cur" should point either to 
                                    * http method first character, 
                                    * or JSON first character '[' */
            if(jsonParser_analyse(cur) == jsonParser_codeInvalidJson){
                httpHeader = httpParser_parse(cur);
            }
            if(httpHeader != NULL){
                switch(httpHeader->httpRoute){
                    case __routeRoot:{
//                        SERVER_HTML_HOME
                        //Send the server page, but wait request-header reception to finish
                        break;
                    } default:{
                        //Send page not found but wait request-header reception to finish
                    }
                }
            }
        }
    }

    return code;   
}

    

/*  "endCh is assumed to point to the end of string ('\0' character")  */
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