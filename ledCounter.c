#include "ledCounter.h"
#include "interval.h"

static int manualCount = 0;
void CountUp() {
    if (!manualCount) {
        static int count = 0;

        LATA = (PORTA & 0xF8) | count;

        ++count;
        count = count % 8;
    }
}
void Count(int number) {
    //Disable CountUp timer
    manualCount = 1;
    
    LATA = (PORTA & 0xF8) | number;
}

void LedCounterBegin() {
    TRISA = 0;
    
    SetInterval(200, CountUp);
}