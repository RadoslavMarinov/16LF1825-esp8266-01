/* 
 * File:   parser.h
 * Author: Riko
 *
 * Created on 15 ???????? 2018, 18:13
 */

#ifndef PARSER_H
#define	PARSER_H

/* PARSER CODES RETURNED BY FUNCTION PARSE*/
#define PARSER_RC_PARSE_msgCompl        0
#define PARSER_RC_PARSE_msgNotCompl     1



typedef enum {
    parserCode_Error = -1,
    parserCode_Ok = 0,
    parserCode_Json = 1,
    parserCode_Ready = 2,
    parserCode_Unknown = 127,       
}Parser_Codes;

typedef void(*Parser_OnMsg)(Parser_Codes code, uint8_t * data, uint16_t len);



Parser_Codes parser_analyse(char * frameStAddr, uint16_t len);
Parser_Codes parser_httpServer(char * frameStAddr, uint16_t len);
uint8_t parser_getTcpConNum(char * startOfLine);



#endif	/* PARSER_H */

