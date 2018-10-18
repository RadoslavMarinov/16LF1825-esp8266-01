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

uint8_t parser_analyse(uint8_t * data, uint16_t len);

#endif	/* PARSER_H */

