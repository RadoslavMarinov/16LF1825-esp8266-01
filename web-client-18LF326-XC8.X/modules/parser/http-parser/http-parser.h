/* 
 * File:   http-parser.h
 * Author: Riko
 *
 * Created on 02 ???????? 2018, 19:18
 */

#ifndef HTTP_PARSER_H
#define	HTTP_PARSER_H

typedef enum {
    __methodInvalid,
    __methodGet,
    __methodPost,
}httpParser_HttpMethod;

typedef enum {
    __routeInvalid = -1,
    __routeRoot,
}httpParser_HttpRoute;

typedef struct {
    httpParser_HttpMethod httpMethod;
    httpParser_HttpRoute httpRoute;
    char * headerStart;
}httpParser_HttpHeader;


httpParser_HttpMethod httpParser_getHttpMethod(char * headerAddr);
httpParser_HttpRoute httpParser_getHttpRoute(char * headerAddr);
httpParser_HttpHeader *  httpParser_parse(char * headerAddr);

#endif	/* HTTP_PARSER_H */

