Chip8 emulator Arduino UNO
==========================

    A chip8 emulator written in C/C++ for Arduino One

##Tutorial:

###Add a chip8 game:

* compile toos/RomFileToArray.cpp  

* drop chip8 game on RomFileToArray.exe in windows  

* in unix system, open the terminal and go to the location of RomFileToArray executable  
  add execution permission whit chmod u+=x to RomFileToArray  
  afterwrite ./RomFileToArray "chip8 game path"  

* the program return 2 file : game.c and game.h  
  include game.h  in MicroChip8.ino  
  set the gamepad input with this table:  

     uint8_t gamepad[16]={  
        0,5,0,0,  
        6,0,0,0,  
        0,0,0,0,  
        8,12,0,0  
        };

* set rom with this code line: 
  Chip8SetRom(chip8,(uint16_t)game,game_SIZE);
    
    

##LICENSES:

###Chip8 emulator Arduino UNO 

    MIT
    
    Copyright (c) 2013 Gabriele Di Bari
    
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:
    
    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.



###TVout:

Files:
    asm_macros.h
    hardware_setup.h
    video_gen.h
    video_gen.cpp
    video_properties.h

    https://code.google.com/p/arduino-tvout/

    Copyright (c) 2010 Myles Metzer
    
    Permission is hereby granted, free of charge, to any person
    obtaining a copy of this software and associated documentation
    files (the "Software"), to deal in the Software without
    restriction, including without limitation the rights to use,
    copy, modify, merge, publish, distribute, sublicense, and/or sell
    copies of the Software, and to permit persons to whom the
    Software is furnished to do so, subject to the following
    conditions:
    
    The above copyright notice and this permission notice shall be
    included in all copies or substantial portions of the Software.
    
    THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND,
    EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES
    OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
    NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
    HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
    WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
    FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
    OTHER DEALINGS IN THE SOFTWARE.
