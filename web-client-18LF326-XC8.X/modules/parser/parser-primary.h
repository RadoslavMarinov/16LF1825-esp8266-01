/* 
 * File:   parser-primary.h
 * Author: Riko
 *
 * Created on 15 ???????? 2018, 18:13
 */

#ifndef PARSER_PRIMARY_H
#define	PARSER_PRIMARY_H
#include "parser.h"

typedef struct {
   Parser_OnMsg onMsgCb; 
}Self;

#define __onMsgCb (parser_self.onMsgCb)

#endif	/* PARSER_PRIMARY_H */

