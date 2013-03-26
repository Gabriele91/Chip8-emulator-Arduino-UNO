#include "TinyHeap.h"
#if TINYHEAPSIZE > 64
    #error "TINYHEAPSIZE max size 64"
#endif
//HEAP BUFFER
HeapBlock heapstack[TINYHEAPSIZE];
//
#define HEAP_TRUE 0xFF
#define HEAP_FALSE 0x00

/* SET/GET VALUE IS SET */
#define GET_VALUE_IS_SET(hashValue) \
((heapstack[hashValue].next & 0x80)>>7)

#define SET_VALUE_IS_SET(hashValue,value)\
heapstack[hashValue].next=\
(heapstack[hashValue].next & 0x7F) | (value& 0x80)

/* SET/GET HAS A NEXT */
#define GET_HAS_NEXT(hashValue) \
((heapstack[hashValue].next & 0x40)>>6)

#define SET_HAS_NEXT(hashValue,value) \
heapstack[hashValue].next=\
((heapstack[hashValue].next & 0xBF) | (value& 0x40))

 /* SET/GET NEXT VALUE */
#define GET_NEXT_VALUE(hashValue)\
(heapstack[hashValue].next & 0x3F)

#define SET_NEXT_VALUE(hashValue,value)\
heapstack[hashValue].next=\
((heapstack[hashValue].next & 0xC0) | (value& 0x3F))

/* new/delete block */
#define NEW_BLOCK(hashValue,ptr,value)\
SET_HAS_NEXT(hashValue,HEAP_FALSE);\
SET_VALUE_IS_SET(hashValue,HEAP_TRUE);\
heapstack[hashValue].value=value;\
heapstack[hashValue].ptr=ptr

#define DELETE_BLOCK(hashValue)\
SET_HAS_NEXT(hashValue,HEAP_FALSE);\
SET_VALUE_IS_SET(hashValue,HEAP_FALSE);\
heapstack[hashValue].value=0;\
heapstack[hashValue].ptr=0

//utility
#define TOSTRING(x) #x
static uint8_t HeapFindVoid(uint8_t hashValue){
    uint8_t loop=0;
    while(loop<TINYHEAPSIZE){
        if(!GET_VALUE_IS_SET(hashValue)) return hashValue;
        ++hashValue;
        ++loop;
    }
    return 255;
}
static uint8_t HeapFindLastNode(uint8_t hashValue){
    uint8_t loop=0;
    while(loop<TINYHEAPSIZE){
       if(!GET_HAS_NEXT(hashValue)) return hashValue;
       hashValue=GET_NEXT_VALUE(hashValue);
       ++loop;
    }
    return 255;
}
//
static void SerialPrintf(char *fmt, ... ){
        char tmp[128]; // resulting string limited to 128 chars
        va_list args;
        va_start (args, fmt );
        vsnprintf(tmp, 128, fmt, args);
        va_end (args);
        Serial.print(tmp);
}

void HeapPrintToSerial(){
   SerialPrintf("\nheap memory[%d]:\n",sizeof(heapstack));
   char binBuffer[33];
    for(int i=0;i<TINYHEAPSIZE;++i){
       itoa (heapstack[i].next,binBuffer,2);
       SerialPrintf("\t"
                    "heap[%d]={"
                    " ptr:%d,"
                    " value? %d,"
                    " value:%d,"
                    " next? %d ,"
                    " next: %d ,"
                    " next bin: %s }"
                    "\n",
                    i,
                    heapstack[i].ptr,
                    GET_VALUE_IS_SET(i),
                    heapstack[i].value,
                    GET_HAS_NEXT(i),
                    GET_NEXT_VALUE(i),
                    binBuffer);
    }
}
void HeapPrintToSerialLite(){
   SerialPrintf("\nheap memory[%d]:\n",sizeof(heapstack));
   char binBuffer[33];
    for(int i=0;i<TINYHEAPSIZE;++i){
		if(GET_VALUE_IS_SET(i)){
		   itoa (heapstack[i].next,binBuffer,2);
		   SerialPrintf("\t"
						"heap[%d]={"
						" ptr:%d,"
						" value? %d,"
						" value:%d,"
						" next? %d ,"
						" next: %d ,"
						" next bin: %s }"
						"\n",
						i,
						heapstack[i].ptr,
						GET_VALUE_IS_SET(i),
						heapstack[i].value,
						GET_HAS_NEXT(i),
						GET_NEXT_VALUE(i),
						binBuffer);
		}
    }
}
//
void HeapInit(){
    memset(heapstack,0,TINYHEAPSIZE*sizeof(HeapBlock));
}

bool HeapAdd(uint16_t ptr,uint8_t value){
    //
    if(HeapIfExistSetValue(ptr,value)) return HEAP_TRUE;
    //heap hash function:
    uint8_t hashValue=ptr%TINYHEAPSIZE;
    //add value
    if(GET_VALUE_IS_SET(hashValue)){
        //have a next?
        if(GET_HAS_NEXT(hashValue)){
            //find last list node
            hashValue=HeapFindLastNode(hashValue);
            //error....
            if(hashValue==255)
                return HEAP_FALSE;
        }
        //find void block
        uint8_t newHash=HeapFindVoid(hashValue);
        //heap full
        if(newHash==255)
            return HEAP_FALSE;
        //add next value
        SET_HAS_NEXT(hashValue,HEAP_TRUE);
        SET_NEXT_VALUE(hashValue,newHash);
        //add value
        NEW_BLOCK(newHash,ptr,value);
        return HEAP_TRUE;
    }
    //add block
    NEW_BLOCK(hashValue,ptr,value);
    return HEAP_TRUE;

}

bool HeapIfExistSetValue(uint16_t ptr,uint8_t value){
    //heap hash function:
    uint8_t hashValue=ptr%TINYHEAPSIZE;
    //
    if(!GET_VALUE_IS_SET(hashValue)) return HEAP_FALSE;
    //
    uint8_t loop=0;
    while(loop<TINYHEAPSIZE){
       // find?
       if(GET_VALUE_IS_SET(hashValue)&&
          heapstack[hashValue].ptr==ptr){
            heapstack[hashValue].value=value;
            return HEAP_TRUE;
       }
       //not find ptr
       if(!GET_HAS_NEXT(hashValue)) return HEAP_FALSE;
       //next
       hashValue=GET_NEXT_VALUE(hashValue);
       ++loop;
    }
    //
    return HEAP_FALSE;
}

bool HeapExist(uint16_t ptr){
    //heap hash function:
    uint8_t hashValue=ptr%TINYHEAPSIZE;
    //
    if(!GET_VALUE_IS_SET(hashValue)) return HEAP_FALSE;
    //
    uint8_t loop=0;
    while(loop<TINYHEAPSIZE){
       // find?
       if(GET_VALUE_IS_SET(hashValue)&&
          heapstack[hashValue].ptr==ptr) return HEAP_TRUE;
       //not find ptr
       if(!GET_HAS_NEXT(hashValue)) return HEAP_FALSE;
       //next
       hashValue=GET_NEXT_VALUE(hashValue);
       ++loop;
    }
    return HEAP_FALSE;
}

uint8_t HeapFind(uint16_t ptr){
    //heap hash function:
    uint8_t hashValue=ptr%TINYHEAPSIZE;
    //
    if(!GET_VALUE_IS_SET(hashValue)) return 255;
    //
    uint8_t loop=0;
    while(loop<TINYHEAPSIZE){
       // find?
       if(GET_VALUE_IS_SET(hashValue)&&
          heapstack[hashValue].ptr==ptr)
            return heapstack[hashValue].value;
       //not find ptr
       if(!GET_HAS_NEXT(hashValue)) return 255;
       //next
       hashValue=GET_NEXT_VALUE(hashValue);
       ++loop;
    }
    //
    return 255;
}

bool HeapRead(uint16_t ptr,uint8_t* valRead){
    //heap hash function:
    uint8_t hashValue=ptr%TINYHEAPSIZE;
    //
    if(!GET_VALUE_IS_SET(hashValue)) return false;
    //
    uint8_t loop=0;
    while(loop<TINYHEAPSIZE){
       // find?
       if(GET_VALUE_IS_SET(hashValue)&&
          heapstack[hashValue].ptr==ptr){
            (*valRead)=heapstack[hashValue].value;
            return true;
        }
       //not find ptr
       if(!GET_HAS_NEXT(hashValue)) return false;
       //next
       hashValue=GET_NEXT_VALUE(hashValue);
       ++loop;
    }
    //
    return false;
}

bool HeapErase(uint16_t ptr){
    //heap hash function:
    uint8_t hashValue=ptr%TINYHEAPSIZE;
    uint8_t lastHash=255;
    //
    if(!GET_VALUE_IS_SET(hashValue)) return false;
    //
    uint8_t loop=0;
    while(loop<TINYHEAPSIZE){
       // find?
       if(GET_VALUE_IS_SET(hashValue)&&
          heapstack[hashValue].ptr==ptr){
            DELETE_BLOCK(hashValue);
            if(lastHash!=255){
               SET_HAS_NEXT(lastHash,HEAP_FALSE);
            }
            return true;
       }
       //not find ptr
       if(!GET_HAS_NEXT(hashValue)) return false;
       //next
       lastHash=hashValue;
       hashValue=GET_NEXT_VALUE(hashValue);
       //
       ++loop;
    }
    //
    return false;
}

//
