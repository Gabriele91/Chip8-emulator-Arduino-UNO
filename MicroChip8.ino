#include <Arduino.h>
#include "render.h"
#include "chip8.h"
#include "gamepad.h"


Chip *chip8;

//#define PLAY_PONG2
//#define PLAY_BRIX
#define PLAY_BLITZ

#ifdef PLAY_PONG2
#include "PONG2.h"
uint8_t gamepad[16]={
	0,5,0,0,
	6,0,0,0,
	0,0,0,0,
	8,12,0,0
};
#elif defined(PLAY_BRIX)
#include "BRIX.h"
uint8_t gamepad[16]={
	2,2,2,2,
	8,2,12,2,
	2,2,2,2,
	2,2,2,5
};
#else
#include "BLITZ.h"
uint8_t gamepad[16]={
	2,2,2,2,
	2,5,2,2,
	2,2,2,2,
	2,2,2,5
};
#endif



unsigned long old_time;

void setup(){	
	Serial.begin(9600);
    //init tv out
    beginScreen(MODE_PAL,64,32);
	forceScaleScreen(3);
    cleanScreen(COLOR_BLACK);
    drawScreen();
    //init input functios:
	//init game pad
	setGamePad(gamepad);
	initGamePad();	
    //init chip8
    Chip8(&chip8);
	//set events
    chip8->input=getEventObject();
    //init rom	
	#ifdef PLAY_PONG2	
		Chip8SetRom(chip8,(uint16_t)PONG2,PONG2_SIZE);
	#elif defined(PLAY_BRIX)	
		Chip8SetRom(chip8,(uint16_t)BRIX,BRIX_SIZE);
	#else
		Chip8SetRom(chip8,(uint16_t)BLITZ,BLITZ_SIZE);
	#endif
	//serial output
	 Serial.begin(9600); 
	 old_time=millis();
}


void loop(){

    //execute chip8 program
    Chip8Execute(chip8);
}
