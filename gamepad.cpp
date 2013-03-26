#include "GamePad.h"

static Event chip8Event;
static uint8_t *gamepadtab;

//event task
unsigned short KeyPress(int i){
    return digitalRead(gamepadtab[i])==HIGH;
}
unsigned short Wait(){
  	for(uint8_t i=0; 1 ;i=(i+1)&0x0f)
		if(digitalRead(gamepadtab[i])==HIGH)
			return i;
}

//set keys
void setGamePad(uint8_t *tabel){
	gamepadtab=tabel;
}
//init game pad
void initGamePad(){
	for(uint8_t i=0;i<16;++i)
		  pinMode(gamepadtab[i], INPUT);	
	chip8Event.KeyPress=KeyPress;
    chip8Event.Wait=Wait;
}
//get event object
Event* getEventObject(){
	return &chip8Event;
}