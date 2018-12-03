
#include "../../../config.h"
#include "http-parser-primary.h"
#include "http-parser.h"
#include "../../utils/utils.h"

httpParser_Self httpParser_self;

httpParser_HttpHeader *  httpParser_parse(char * headerAddr){
    char * cur = headerAddr;
    httpParser_HttpMethod  method;
    httpParser_HttpRoute route;
    
    httpParser_HttpHeader * headerStrAddress;
    headerStrAddress = &(__header);
    
    
    method = httpParser_getHttpMethod(cur);
    if(method != __methodInvalid){
        __setMethod(__methodGet);
        __setHeaderStart(headerAddr);
        route = httpParser_getHttpRoute(headerAddr);
        return headerStrAddress;
    }
    
    return NULL;
}


httpParser_HttpMethod httpParser_getHttpMethod(char * headerAddr){

    if(strncmp("POST", headerAddr, 4) == 0){
        return __methodPost;
    } else if(strncmp("GET", headerAddr, 3) == 0) {
        return __methodGet;
    } else {
        return __methodInvalid;
    }
}

httpParser_HttpRoute httpParser_getHttpRoute(char * headerAddr){
    char * cur = headerAddr;
    while(*cur != '/'){
        cur++;
    }
    if(strncmp("/ ", cur, 2)==0){
        return __routeRoot;
    } else {
        return __routeInvalid;
    }
        
}




