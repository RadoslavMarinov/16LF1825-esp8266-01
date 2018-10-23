/* 
 * File:   json-parser-primary.h
 * Author: Riko
 *
 * Created on 23 ???????? 2018, 16:43
 */

#ifndef JSON_PARSER_PRIMARY_H
#define	JSON_PARSER_PRIMARY_H

#include "json-parser.h"

#define KEY_MAX_LEN             10U
#define VAL_MAX_LEN             20U    

typedef struct {
    unsigned int invalidJson :1;
    unsigned int keyArrayTooLong :1;
}Error;

typedef struct {
    
    union {
        char strValue[VAL_MAX_LEN + 1];  //+1 for the null character
        uint16_t numValue;
    };
    char key[KEY_MAX_LEN + 1];      //+1 for the null character
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
#define __raiseErr(err)     do { __errors.err = 1; }while(0)

/*******************************************************************************
 * KEY VALUE PAIR
 ******************************************************************************/
#define __keyVal            ( jsonParser_self.keyVal )

//Key
#define __keyArr            ( __keyVal.key )
#define __keyArrLastAddr    (&(__keyArr[KEY_MAX_LEN - 1]))

// Value
#define __valArr            ( __keyVal.strValue )
#define __valNum            ( __keyVal.numValue )

// Is Value Numerical or String
#define __isValStr          ( __keyVal.isValueString )



static char* processKeyValue(char * keyStAddr);

/* Return last address of the key array */
static char* copyKey(char * keyStAddr);
static char* copyVal(char * valStAddr );
static uint16_t getNumfromStr(char * numStr);
#endif	/* JSON_PARSER_PRIMARY_H */

