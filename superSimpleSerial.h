#ifndef SUPER_SIMPLE_SERIAL
#define SUPER_SIMPLE_SERIAL

#include "globals.h"

//Start the super simple serial system (19200 Baud Rate)
void SuperSimpleSerialBegin();

//Write a byte of data
void Sout(char byte);

#if 1
void putch(char);
#endif

#endif