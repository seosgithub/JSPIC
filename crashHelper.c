#include "crashHelper.h"

//Helps catch crashes on interrupts (Will go back to this)
static int IsCrashed = 0;

void Crash(int id) {
    IsCrashed = 1;
    TRISA = 0;

    LATA = (PORTA & 0xF8) | id;

    while (1);
}