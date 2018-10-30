
#include "json-parser-primary.h"
#include "json-parser.h"
#include "../../comander/comander.h"

static Self jsonParser_self;


uint8_t jsonParser_analyse(char * lastAddr){
    
    char * data;
#ifdef UNDER_TEST
    uint16_t jsonStrLen = 0; 
#endif
    data = lastAddr;
//    TODO: check if json is too long!
    while( (*data) != '{' ){
#ifdef UNDER_TEST
        if( jsonStrLen++ > JSON_MAX_STR_LEN ){
            __raiseErr(jsonStrTooLong);
            CONFIG_stopHere();
        }
#endif
        data--;
    }

    while((*data) != '}' ){
        data++;
        // data now points to key open quote
        data = jsonParser_parse(data); //Data is now in Self data
        /* Data now points either to closing '"' , or at the last character of 
         the number */
        commander_execute(__keyArr, __valArr);
        data ++;
        // data now points to key open quote
    }
    
    
    return 0;
}

// Returns 
char * jsonParser_parse( char * keyStartAddr ){ // startAddr should point to '{'

    char * data;            
    data = keyStartAddr;  //Data should point to '"'
#ifdef UNDER_TEST
    if(*data != '"'){
        __raiseErr(invalidJson);
        CONFIG_stopHere();
    }
#endif
    data++; //Expected key first char
    data = parseKeyValuePair(data);
    return data;
}

static char* parseKeyValuePair(char * keyStAddr){
    char * data;
    data = keyStAddr;
    data = copyKey(data); // data should point to key`s closing quot. mark
    data += 2;            /* data should point to val`s opening quotation mark
                           *  or first value numerical character */
    data = copyVal(data); /* data should point to val`s closing
                           *  quotation mark (if value alphabetical is string), 
                           or last numerical character (if "value" is alphanumerical string)*/
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
        __valNum = getNumFromStr(src, &src);
        __isValStr = false;
    }
    return src;
}

static uint16_t getNumFromStr(char * numStrStAddr, char **numStrLastAddr){
    uint16_t power = 1;
    char *endAddr;
    char * dig;
    uint16_t val = 0;
    dig = numStrStAddr;
    while(*dig >= '0' && *dig <= '9'){
        dig++;
    }
    endAddr = --dig;
    while( dig >= numStrStAddr ){
        val += ( (*dig) - 48 ) * power;
        power *= 10;
        dig--;
    }
    *numStrLastAddr = endAddr;
    return val;
}