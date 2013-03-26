#include <Arduino.h>
#include "PONG2.h"
#include "TETRIS.h"
#include "render.h"
#include "chip8.h"
#include "gamepad.h"

Chip *chip8;
uint8_t gamepad[16]={
	0,5,0,0,
	6,0,0,0,
	0,0,0,0,
	8,12,0,0
};




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
    Chip8SetRom(chip8,(uint16_t)PONG2,PONG2_SIZE);
	
}

void loop(){
    //execute chip8 program
    Chip8Execute(chip8);
}
