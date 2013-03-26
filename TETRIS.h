#ifndef TETRIS_H
#define TETRIS_H


#include <avr/pgmspace.h>


#ifdef __cplusplus
extern "C" {
#endif

#define TETRIS_SIZE 494

extern PROGMEM  unsigned char TETRIS[TETRIS_SIZE];

#ifdef __cplusplus
};
#endif
#endif