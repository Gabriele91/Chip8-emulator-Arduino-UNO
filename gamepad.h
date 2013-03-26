#ifndef GAMEPAD_H
#define GAMEPAD_H

#include "Config.h"
#include "chip8.h"

//set keys
void setGamePad(uint8_t *tabel);
//init game pad
void initGamePad();
//get event object
Event* getEventObject();



#endif