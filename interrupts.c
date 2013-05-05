#include "interrupts.h"

interrupt void onInterrupt() {
    //Millisecond timer
    //###########################################
    if (INTCONbits.TMR0IF) {
        INTCONbits.TMR0IF = 0;
        OnIntervalInterrupt();
    }
    //###########################################

    //i2c
    //###########################################
    else if (SSPIF) {
        SSPIF = 0;

        //I2C Slave (J-Wire Implementation)
        if (jWireEnabled) {
            JWireOnInterrupt();
        }

        //I2C Master
        if (wireMasterEnabled) {
            WireOnInterrupt();
        }
    }
    //###########################################

    //Serial (JSerial Implementation)
    //###########################################
    else if (RCIF) {
        OnSerialInterrupt();
    }

    else if (TXIF) {
        SerialWriteInterrupt();
    }
    //###########################################

    //Catch crashes overriden by interrupts if possible
    if (IsCrashed) {
        Crash(7);
    }
}