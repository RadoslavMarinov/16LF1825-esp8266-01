
#include "../../config.h"
#include "utils-primary.h"
#include "utils.h"


/*
 * Return the address of the substring if exist. Otherwise NULL
 */
char * utils_substring(const char * subStr, const char * superStr){

	char * sup;
	char * csupr;
	char * sub;

	sup  = (char*)superStr;
	sub = (char*)subStr;

	while(*sup != '\0'){
		csupr = sup;
		while(*sub == *csupr && *sub != '\0'){
			sub++;
			csupr++;
		}

		if(*sub == '\0'){
			return sup;
		} else {
			sup++;
			sub = (char*)subStr;
		}
	}

    return NULL;
}

//uint8_t utils_stringStartsWith(char * subStr, superStr) {
//    if(strncmp(subStr, superStr, strlen(subStr)) == 0){
//        return true;
//    }
//    return false; 
//}