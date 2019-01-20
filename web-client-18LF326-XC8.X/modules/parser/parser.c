#include "../../config.h"
#include "parser-primary.h"
#include "parser.h"
#include "../receiver/receiver.h"
#include "../transmitter/transmitter.h"
#include "../timer/timer.h"
#include "string.h"
#include "json-parser/json-parser.h"
#include "http-parser/http-parser.h"
#include "../utils/utils.h"
#include "../server/server.h"
#include "../client/client.h"

parser_Self parser_self;

/* Detects if frame is terminat*/

Parser_Codes parser_httpClient(char * frameStAddr, uint16_t len) {
    char * cur = (char *)( frameStAddr + (len - 1) ); /*  "curr"should point to '\0'
                                                        * which is the end of the string/frame
                                                        */  

    char * strStart = NULL;
    Parser_Codes code = parserCode_Unknown;
    strStart = cur = getStartOfStr(cur, len);
    
    
    if(*cur == '{'){
        if(jsonParser_analyse(cur) == jsonParser_codeInvalidJson){
           CONF_raiseNvErrBit(conf_nvErr_parser_msgStartsWithOpenBracketButNotJSON);
        } else {
            client_raiseEvenUpdateServer();
        }
    }
    else if(strcmp("upd", cur) == 0){
        client_raiseEvenUpdateServer();
    } else if(strcmp("OK", cur) == 0){
        client_raiseEventMsgOk();
    }else if(strcmp("SEND OK", cur) == 0){
        client_raiseEventMsgOk();
    }else if(strcmp("ack", cur) == 0){
        client_raiseEventAck();
    } else if(strcmp("ERROR", cur) == 0){
        client_raiseEventError();
    }
    receiver_resetFrBuff();
//    else if()
    
    return code;
    
  
}

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
    }else if(strcmp(curr, "FAIL") == 0 ){
        code = parserCode_fail;
    } else {
        return parserCode_Unknown;
    }
    return code;
}
void sendServerEventSendRootData(void){
    receiver_resetFrBuff();
    server_raiseEventSendData(server_routeRoot, server_httpMethodGet);    
}

void sendServerEvSendNotFound(void){
    receiver_resetFrBuff();
    server_raiseEventSendData(server_routeInvalid, server_httpMethodGet);
}

void sendEventServerResponseOk(void){
    receiver_resetFrBuff();
    server_raiseEventSendData(server_routeRoot, server_httpMethodPost);
}
/*
 * This is the parser call-back function used when device starts the TCP server
 */
Parser_Codes parser_httpServer(char * frameStAddr, uint16_t len) {
    char * cur = (char *)( frameStAddr + (len - 1) ); /*  "curr"should point to '\0'
                                                        * which is the end of the string/frame
                                                        */  
    char * substrStart = NULL;
    char * strStart = NULL;
    Parser_Codes code = parserCode_Unknown;
    httpParser_HttpHeader *httpHeader = NULL;
    strStart = cur = getStartOfStr(cur, len);
 
    
    if(strcmp("OK", cur) == 0){
        server_raiseEventMsgOk();
    }
    else if(strcmp("SEND OK", cur) == 0){
        server_raiseEventMsgOk();
    }
    else if( strncmp("+IPD", cur, 4) == 0 ){
//        if(parser_getTcpConNum(strStart)){
//
//         }
        
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
                
                switch(httpHeader->httpMethod){
                    
                    // == METHOD GET
                    case __methodGet :{
                        switch(httpHeader->httpRoute){
                            case __routeRoot:{
                                timer_start(5, sendServerEventSendRootData);
        //                        SERVER_HTML_HOME
                                //Send the server page, but wait request-header reception to finish
                                break;
                            } case __routeInvalid:{
                                timer_start(5, sendServerEvSendNotFound);
                                //Send page not found but wait request-header reception to finish
                            }
                        } 
                        break;
                    }
                    // == METHOD POST
                    case  __methodPost:{
                        switch(httpHeader->httpRoute){
                            case __routeRoot:{
                                __enableJsonParser();
                                
                                break;
                            } case __routeInvalid:{
                                
                                break;
                            }
                        }
//                        receiver_resetFrBuff();
                        break;
                    }
                    // == METHOD GET
                    case __methodInvalid:{
                        receiver_resetFrBuff();
                        break;
                    }
                } //METHOD DISPATCHER END
                
            }
        }
    }
    // END OF +IPD prefix
    else if( __jsonParersEnabled && (*strStart) == '{' ){
        if( jsonParser_codeValidJson == jsonParser_analyse(strStart) ){
            
            timer_start(5, sendEventServerResponseOk);
            __disableeJsonParser();
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

//if number is greater than 9 - return 255
//startOfLine should point to the begginnig of the the "+IPD" line
//uint8_t parser_getTcpConNum(char * startOfLine){
//    
//    do{
//        startOfLine++;
//    }while(*startOfLine != ',');
//    if( *(startOfLine+1) != ','){
//        return 0xFF;
//    }
//    return (*startOfLine) - 48;
//}