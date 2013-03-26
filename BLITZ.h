#ifndef BLITZ_H
#define BLITZ_H


#include <avr/pgmspace.h>


#ifdef __cplusplus
extern "C" {
#endif

#define BLITZ_SIZE 391

extern PROGMEM  unsigned char BLITZ[BLITZ_SIZE];

#ifdef __cplusplus
};
#endif
#endif