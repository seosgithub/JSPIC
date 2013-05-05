#include "superSimpleSerial.h"

void SuperSimpleSerialBegin() {
    TX9 = 0;
    TXEN = 1;                  // transmit enable
    SYNC = 0;                  // async mode

    //Configure baud-rate to 57kbits/s
    BRGH = 1;
    BRG16 = 1;
    SPBRG = 34;

    TRISCbits.RC7 = 1;
    TRISCbits.RC6 = 1;
    RX9 = 0;                   // 8-bit reception
    SPEN = 1;                  // serial port enable
    CREN = 0;                  // clear enable first
    CREN = 1;                  // now enable
    TXIF = 0;
}

void Sout(char byte) {
    //Block till we can write to the register
    while (!TXIF);
    
    TXREG = byte;
}

#if 1
void putch(char byte) {
    Sout(byte);
}
#endif