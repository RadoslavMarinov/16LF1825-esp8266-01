/* 
 * File:   json-parser.h
 * Author: Riko
 *
 * Created on 23 ???????? 2018, 16:43
 */

#ifndef JSON_PARSER_H
#define	JSON_PARSER_H

#include "../../../config.h"

uint8_t jsonParser_analyse(char * lastAddr);
void jsonParser_parse( char * startAddr );

#endif	/* JSON_PARSER_H */

