#ifndef __MAIN_H__
#define __MAIN_H__

typedef struct {
    unsigned int comander:1;
    unsigned int communicator:1;
    unsigned int eeprom:1;
    unsigned int esp:1;
    unsigned int parser:1;
    unsigned int json_parser:1;
    unsigned int receiver:1;
    unsigned int timer:1;
    unsigned int transmitter:1;
    unsigned int server:1;
    unsigned int client:1;
} main_AppErrors;

typedef struct {
    main_AppErrors appErrs;
}main_Self;


extern main_Self main_self;
extern void main_init(void);
void main_setLed(void * data);
void gpio_init(void);
void main_reset(void);
void config_dummyFunc(void);

#endif