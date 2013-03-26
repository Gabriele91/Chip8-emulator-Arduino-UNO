#ifndef TINYHEAP_H
#define TINYHEAP_H

#include "Config.h"
#include "TinyHeapConfig.h"
//
struct HeapBlock {
    uint8_t  value;
    uint8_t  next;
    uint16_t ptr;
};
//
void HeapPrintToSerial();
void HeapInit();
bool HeapAdd(uint16_t ptr,uint8_t value);
bool HeapExist(uint16_t ptr);
bool HeapIfExistSetValue(uint16_t ptr,uint8_t value);
uint8_t HeapFind(uint16_t ptr);
bool HeapRead(uint16_t ptr,uint8_t* valRead);
bool HeapErase(uint16_t ptr);
//

#endif // TINYHEAP_H
