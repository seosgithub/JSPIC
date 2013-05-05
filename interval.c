#include "interval.h"

#define MAX_INTERVALS 4

//Store function pointer and delay time
typedef struct INTERVAL_CALLBACK_T {
    void (*function)();
    short delay;
} IntervalCallback_t;
static IntervalCallback_t callbacks[MAX_INTERVALS];

//Handle interval timings in userland
void IntervalTick() {
    static short time = 0;

    for (int i = 0; i < MAX_INTERVALS; ++i)
        if (callbacks[i].function && (time % callbacks[i].delay == 0))
            callbacks[i].function();

     ++time;
}

void OnIntervalInterrupt() {
    //Que the handlers
    AsyncBlank(IntervalTick);
}

void SetInterval(int delayInMs, void (*callbackToUse)()) {
    delayInMs = delayInMs / 4;
    //Lazy load
    static char hasLoaded = 0;
    if (!hasLoaded) {
        //Timer 0 interrupt at 1 second
        T0CONbits.TMR0ON = 1;
        T0CONbits.T08BIT = 1; //Divide timer by 256
        T0CONbits.T0CS = 0; //Use internal clock for timing
        T0CONbits.PSA = 0;
        T0CONbits.T0PS = 4;
        INTCONbits.TMR0IE = 1;

        for (int i = 0; i < MAX_INTERVALS; ++i)
            callbacks[i].function = NULL;
        
        hasLoaded = 1;
    }

    for (int i = 0; i < MAX_INTERVALS; ++i) {
        if (callbacks[i].function == NULL) {
            callbacks[i].function = callbackToUse;
            callbacks[i].delay = delayInMs;
            break;
        }
    }
}