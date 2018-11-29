/* 
 * File:   json-parser-primary.h
 * Author: Riko
 *
 * Created on 23 ???????? 2018, 16:43
 */

#ifndef JSON_PARSER_PRIMARY_H
#define	JSON_PARSER_PRIMARY_H

#include "../../../config.h"
#include "json-parser.h"

#define MODULE_NAME json_parser

/******************************************************************************* 
 * CONDITIONALS
 ******************************************************************************/
#ifdef CONFIG_raiseError
    #define __addGlobalError()   do{CONFIG_raiseError(MODULE_NAME);}while(0)
#else
    #define __addGlobalError()   
#endif



typedef struct {
    unsigned int invalidJson :1;
    unsigned int keyArrayTooLong :1;
    unsigned int jsonStrTooLong :1;
}Error;

typedef struct {
    
    union {
        char strValue[JSON_VAL_MAX_LEN + 1];  //+1 for the null character
        uint16_t numValue;
    };
    char key[JSON_KEY_MAX_LEN + 1];      //+1 for the null character
    unsigned int isValueString : 1;
    
}KeyValuePair;

typedef struct {
    Error errors;  
    KeyValuePair keyVal;
}Self;

/*******************************************************************************
 * ERRORS
 ******************************************************************************/
#define __errors            (jsonParser_self.errors)
#define __raiseErr(err)     do { __errors.err = 1; __addGlobalError(); }while(0)

/*******************************************************************************
 * KEY VALUE PAIR
 ******************************************************************************/
#define __keyVal            ( jsonParser_self.keyVal )

//Key
#define __keyArr            ( __keyVal.key )
#define __keyArrLastAddr    (&(__keyArr[JSON_KEY_MAX_LEN - 1]))

// Value
#define __valArr            ( __keyVal.strValue )
#define __valNum            ( __keyVal.numValue )

// Is Value Numerical or String
#define __isValStr          ( __keyVal.isValueString )



static char* parseKeyValuePair(char * keyStAddr);

/* Return last address of the key array */
static char* copyKey(char * keyStAddr);
static char* copyVal(char * valStAddr );
static uint16_t getNumFromStr(char * numStrStAddr, char **numStrLastAddr);


#ifndef JSON_KEY_MAX_LEN
#error "Missing required: JSON_KEY_MAX_LEN "
#endif

#ifndef JSON_VAL_MAX_LEN
#error "Missing required: JSON_VAL_MAX_LEN "
#endif

#ifndef JSON_MAX_STR_LEN
#error "Missing required: JSON_MAX_STR_LEN "
#endif


#endif	/* JSON_PARSER_PRIMARY_H */

