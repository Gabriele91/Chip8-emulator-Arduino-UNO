#ifndef BRIX_H
#define BRIX_H


#include <avr/pgmspace.h>


#ifdef __cplusplus
extern "C" {
#endif

#define BRIX_SIZE 280

extern PROGMEM  unsigned char BRIX[BRIX_SIZE];

#ifdef __cplusplus
};
#endif
#endif