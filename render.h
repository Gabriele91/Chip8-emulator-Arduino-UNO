#ifndef RENDER_H
#define RENDER_H

#include "Config.h"

#define MODE_PAL 1
#define MODEL_NTSC 0
#define COLOR_WHITE 0xFF
#define COLOR_BLACK 0x00
//setup scene
void beginScreen(uint8_t mode,uint8_t w,uint8_t h);
//scale image
void forceScaleScreen(char sfactor);
//get color pixel
uint8_t getScreenColor(uint8_t x,uint8_t y);
//set color pixel
void setScreenColor(uint8_t color,uint8_t x,uint8_t y);
//set invers color
void setScreenInvers(uint8_t x,uint8_t y);
//draw screen
void drawScreen();
//clear screen whit a color
void cleanScreen(uint8_t color);

#endif
