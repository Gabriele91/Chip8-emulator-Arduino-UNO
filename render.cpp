#include "render.h"

//global screen buffer
uint8_t *buffer_screen;
//

void beginScreen(uint8_t mode,uint8_t width,uint8_t height){
	/* TV OUT SETTING */
	// check if x is divisable by 8
	if (!(width & 0xF8)){
		return; 
	}
	else {
		width/=8;
	}
	//gen buffer
	buffer_screen=(uint8_t*)malloc(width * height *sizeof(uint8_t));
	//setup screen
	render_setup(mode,width,height,buffer_screen);
	cleanScreen(COLOR_BLACK);
}

void forceScaleScreen(char sfactor) {
	drawScreen();
	display.vscale_const = sfactor - 1;
	display.vscale = sfactor - 1;
}

uint8_t getScreenColor(uint8_t x,uint8_t y){
	return (buffer_screen[(x>>3)+(y*display.hres)]&((0x80)>>(x%8))) ? 0xFF : 0x00;
}

void setScreenColor(uint8_t color,uint8_t x,uint8_t y){
	buffer_screen[(x>>3)+(y*display.hres)]|=(color&0x80)>>(x%8);
}

void setScreenInvers(uint8_t x,uint8_t y){
	buffer_screen[(x>>3)+(y*display.hres)]^=(0x80)>>(x%8);
}

void drawScreen(){
	int stop_line = (int)(display.start_render + (display.vres*(display.vscale_const+1)))+1;
	while (display.scanLine != stop_line);
	while (display.scanLine == stop_line);
}

void cleanScreen(uint8_t color){
	memset(buffer_screen,color,display.hres * display.vres*sizeof(uint8_t));
}
