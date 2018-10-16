# 1 "modules/parser/parser.c"
# 1 "<built-in>" 1
# 1 "<built-in>" 3
# 288 "<built-in>" 3
# 1 "<command line>" 1
# 1 "<built-in>" 2
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\language_support.h" 1 3
# 2 "<built-in>" 2
# 1 "modules/parser/parser.c" 2
# 1 "modules/parser/../../config.h" 1
# 11 "modules/parser/../../config.h"
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 1 3



# 1 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\musl_xc8.h" 1 3
# 4 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 1 3
# 135 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef unsigned long uintptr_t;
# 150 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef long intptr_t;
# 166 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef signed char int8_t;




typedef short int16_t;




typedef long int32_t;
# 189 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef int32_t intmax_t;







typedef unsigned char uint8_t;




typedef unsigned short uint16_t;




typedef unsigned long uint32_t;
# 225 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/alltypes.h" 3
typedef uint32_t uintmax_t;
# 22 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3


typedef int8_t int_fast8_t;




typedef int8_t int_least8_t;
typedef int16_t int_least16_t;
typedef int32_t int_least32_t;




typedef uint8_t uint_fast8_t;




typedef uint8_t uint_least8_t;
typedef uint16_t uint_least16_t;
typedef uint32_t uint_least32_t;
# 131 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 3
# 1 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\bits/stdint.h" 1 3
typedef int32_t int_fast16_t;
typedef int32_t int_fast32_t;
typedef uint32_t uint_fast16_t;
typedef uint32_t uint_fast32_t;
# 131 "C:\\Program Files\\Microchip\\xc8\\v2.00\\pic\\include\\c99\\stdint.h" 2 3
# 11 "modules/parser/../../config.h" 2
# 1 "modules/parser/parser.c" 2

# 1 "modules/parser/parser-primary.h" 1
# 2 "modules/parser/parser.c" 2

# 1 "modules/parser/parser.h" 1
# 11 "modules/parser/parser.h"
void parser_analyse(uint8_t * data, uint8_t size);
# 3 "modules/parser/parser.c" 2



void parser_analyse(uint8_t * data, uint8_t size) {
    if(*data){
        size++;
    }
}
