#include "flipper.h"

static int hasSetup = 0;

void FlipLazyBegin() {
    if (!hasSetup) {
        TRISBbits.RB3 = 0;
        TRISBbits.RB4 = 0;
        TRISBbits.RB5 = 0;
        TRISBbits.RB6 = 0;
        TRISBbits.RB7 = 0;

        LB7 = 0;
        LB6 = 0;
        LB5 = 0;
        LB4 = 0;
        LB3 = 0;
    }

    hasSetup = 1;
}

void FlipA() {
    FlipLazyBegin();
    
    for (int i = 0; i < 4; ++i)
        RB7 = ~RB7;
}

void FlipB() {
    FlipLazyBegin();

    for (int i = 0; i < 4; ++i)
        RB6 = ~RB6;
}

void FlipC() {
    FlipLazyBegin();

    for (int i = 0; i < 4; ++i)
        RB5 = ~RB5;
}

void FlipD() {
    FlipLazyBegin();

    for (int i = 0; i < 4; ++i)
        RB4 = ~RB4;
}

void FlipE() {
    FlipLazyBegin();

    for (int i = 0; i < 4; ++i)
        RB3 = ~RB3;
}