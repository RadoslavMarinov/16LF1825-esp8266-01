
#include "json-parser-primary.h"
#include "json-parser.h"

static Self jsonParser_self;


uint8_t jsonParser_analyse(char * lastAddr){
    
    char * data;
    data = lastAddr;
//    TODO: check if json is too long!
    while( (*data) != '{' ){
        data--;
    }
    jsonParser_parse(data);
    return 0;
}

void jsonParser_parse( char * startAddr ){

    char * data;
    data = startAddr + 1 ;  //Expected quotation mark
#ifdef UNDER_TEST
    if(*data != '"'){
        __raiseErr(invalidJson);
        CONFIG_stopHere();
    }
#endif
    data++; //Expected key first char
    data = processKeyValue(data);
}

static char* processKeyValue(char * keyStAddr){
    char * data;
    data = keyStAddr;
    data = copyKey(data); // data should point to key`s closing quot. mark
    data += 2;            // data should point to val`s closing quot. mark if exist!
    copyVal(data);
    return data;
}

static char* copyKey(char * keyStAddr){
    char* src, *dst;
    
    src = keyStAddr;
    dst = (char*)__keyArr;
    
    while(*src != '"'){
       *dst++ = *src++; 
    }
    *dst = '\0';
    
#ifdef UNDER_TEST
    if( dst > __keyArrLastAddr){
        __raiseErr(invalidJson);
        CONFIG_stopHere();
    }
#endif
    return src;
}



static char* copyVal(char * valStAddr ){
    char *src, *dst;
    
    dst = (char*)__valArr;
    src = valStAddr;
    if(*src == '"'){
        __isValStr = true;
        src++;
        
        while(*src != '"'){
           *dst++ = *src++; 
        }
        *dst = '\0';
        
    } else {
        __valNum = getNumfromStr(src);
      return src;  
    }
    return src;
}

static uint16_t getNumfromStr(char * numStr){
    uint16_t power = 1;
    char *endAddr;
    char * dig;
    dig = numStr;
    uint16_t val = 0;
    while(*dig >= '0' && *dig <= '9'){
        dig++;
    }
    endAddr = --dig;
    while( dig >= numStr ){
        val += ( (*dig) - 48 ) * power;
        power *= 10;
        dig--;
    }
    numStr = endAddr;
    return val;
}