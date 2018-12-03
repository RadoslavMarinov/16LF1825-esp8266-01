/* 
 * File:   json-parser.h
 * Author: Riko
 *
 * Created on 23 ???????? 2018, 16:43
 */

#ifndef JSON_PARSER_H
#define	JSON_PARSER_H

#include "../../../config.h"

typedef enum{
    jsonParser_codeInvalidJson,
    jsonParser_codeValidJson,            
}jsonParser_Code;

/* !NOTE: JSON format does not support nested objects!
 * Params:
 *    startAddr: should point to JSON first character '{'
 */ 
jsonParser_Code jsonParser_analyse(char * startAddr);
char * jsonParser_parse( char * keyStartAddr );

#endif	/* JSON_PARSER_H */

