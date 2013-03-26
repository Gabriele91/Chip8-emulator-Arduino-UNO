/*!
 * \author Gabriele Di Bari
 * \date 2011/06/15
 * \details translation comments on 2013/03/23
 */
#ifndef CHIP_H
#define CHIP_H
#define _DEBUG_

#include "Config.h"

/*!
 * \struct event management
 */
typedef struct _Event{
    unsigned short (*KeyPress)(int i);
    unsigned short (*Wait)();
}Event;
/*!
 * \struct chip memory
 */
struct _Memory;
typedef struct _Memory Memory;
/*!
 * \struct rom
 */
typedef uint16_t _Rom;
typedef uint16_t Rom;
/*!
 * \struct chip
 */
struct _Chip;
typedef struct _Chip{

    /*!
     * \var Memory* memory
     * \brief cpu memory
     */
    Memory* memory;
    /*!
     * \var Event* input
     * \brief input event
     */
    Event*  input;

}Chip;

/*!
 * \fn Chip8
 * \brief initializes the cpu
 * \param chip a struct _Chip **
 */
void Chip8(struct _Chip **chip);
int  Chip8Execute(struct _Chip *chip);
void Chip8SetRom(struct _Chip *chip,uint16_t rom,uint16_t romsize);
void Chip8Free(struct _Chip **chip);
#endif
