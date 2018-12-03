/* 
 * File:   http-parser-primary.h
 * Author: Riko
 *
 * Created on 02 ???????? 2018, 19:17
 */

#ifndef HTTP_PARSER_PRIMARY_H
#define	HTTP_PARSER_PRIMARY_H

#include "http-parser.h"





typedef struct{
    httpParser_HttpHeader header;
}httpParser_Self;

// == Header
#define __header                        (httpParser_self.header)
//Header Method
#define __method                        (__header.httpMethod)
#define __setMethod(method)             do{ __method = (method); }while(0)
//Header Route
#define __route                         (__header.httpRoute)
#define __setRoute(route)               do{ __route = (route); }while(0)
//Header Start Addr
#define __headerStart                   (__header.headerStart)
#define __setHeaderStart(addr)          do{ __headerStart = (addr); }while(0)
 


// PRIVATE METHOD DECLARATIONS
httpParser_HttpMethod getHttpMethod(char * headerAddr);

#endif	/* HTTP_PARSER_PRIMARY_H */

