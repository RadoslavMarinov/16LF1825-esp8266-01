/* 
 * File:   parser-primary.h
 * Author: Riko
 *
 * Created on 15 ???????? 2018, 18:13
 */

#ifndef PARSER_PRIMARY_H
#define	PARSER_PRIMARY_H

#define MODULE_NAME parser

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif


typedef struct {
}Self;


static char * getStartOfStr(char * endCh, uint16_t len);

#endif	/* PARSER_PRIMARY_H */

