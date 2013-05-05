#include "jspic.h"

#pragma config OSC = IRCIO7    // Oscillator Selection bits (Internal oscillator block, port function on RA7, clock on RA6)
#pragma config FCMEN = OFF      // Fail-Safe Clock Monitor Enable bit (Fail-Safe Clock Monitor disabled)
#pragma config IESO = OFF       // Internal/External Oscillator Switchover bit (Oscillator Switchover mode disabled)

// CONFIG2L
#pragma config PWRT = OFF       // Power-up Timer Enable bit (PWRT disabled)
#pragma config BOREN = OFF      // Brown-out Reset Enable bits (Brown-out Reset disabled in hardware and software)
#pragma config BORV = 3         // Brown-out Reset Voltage bits (VBOR set to 2.1V)

// CONFIG2H
#pragma config WDT = OFF        // Watchdog Timer Enable bit (WDT disabled (control is placed on the SWDTEN bit))
#pragma config WDTPS = 32768    // Watchdog Timer Postscale Select bits (1:32768)

// CONFIG3H
#pragma config PBADEN = OFF     // PORTB A/D Enable bit (PORTB<4:0> pins are configured as digital I/O on Reset)
#pragma config LPT1OSC = OFF    // Low-Power Timer 1 Oscillator Enable bit (Timer1 configured for higher power operation)
#pragma config MCLRE = ON       // MCLR Pin Enable bit (MCLR pin enabled; RE3 input pin disabled)

// CONFIG4L
#pragma config STVREN = OFF     // Stack Full/Underflow Reset Enable bit (Stack full/underflow will not cause Reset)
#pragma config LVP = OFF        // Single-Supply ICSP Enable bit (Single-Supply ICSP disabled)
#pragma config BBSIZ = 1024     // Boot Block Size Select bits (1K words (2K bytes) Boot Block)

int main() {
    //Set clock to 2MHZ (FOSC = 8MHZ)
    OSCCONbits.IRCF = 7;
    //PLLEN = 1;

    //Custom JSPic debugging platform (Uses port B)
    MacawBegin();

    //Allows you to use Sout to write a byte of data to serial
    SuperSimpleSerialBegin();
    
    AsyncBegin();
    onSetup();
    
    GIE = 1;
    PEIE = 1;

    //Start counter on LA0-2, should tick up at 500ms per count
    LedCounterBegin();

    while (1) {
        onLoop();
        AsyncTick();
    }
}