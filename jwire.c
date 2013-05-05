#include "jwire.h"

#define MAX_MESSAGE_SIZE 150

//Handlers
static AsyncCallback_t receiveCallback = 0;
static AsyncCallback_t requestCallback = 0;

#define WriteGotAddress (SSPSTATbits.S == 1 && SSPSTATbits.R_W == 0 && SSPSTATbits.D_A == 0 && SSPSTATbits.BF == 1)
#define WriteGotData ((SSPSTATbits.S == 1 || SSPSTATbits.P == 1) && SSPSTATbits.R_W == 0 && SSPSTATbits.D_A == 1 && SSPSTATbits.BF == 1)
#define ReadGotAddress (SSPSTATbits.S == 1 && SSPSTATbits.R_W == 1 && SSPSTATbits.D_A == 0)
#define ReadGotData (SSPSTATbits.S == 1 && SSPSTATbits.R_W == 1 && SSPSTATbits.D_A == 1 && SSPSTATbits.BF == 0)
#define ReadDone (SSPSTATbits.S == 1 && SSPSTATbits.D_A == 1 && SSPSTATbits.BF == 0 && CKP == 1)

static char buffer[MAX_MESSAGE_SIZE];
static int bufferReadPos = 0;
static int bufferWritePos = 0;

static int jWireEnabled = 0;

#include <stdio.h>
//I2C interrupted us
void JWireOnInterrupt() {
    //Master is about to write us some data
    if (WriteGotAddress) {
        int addr = SSPBUF;
        CKP = 1;

        //Get ready for data!
        bufferReadPos = 0;
    }

    //Master is writing us some data
    if (WriteGotData) {
        int data = SSPBUF;

        //Read some data!
        buffer[bufferReadPos] = data;

        if (bufferReadPos == sizeof(Packet_t)-1) {
            if (receiveCallback) {
                Async(receiveCallback, buffer, sizeof(Packet_t));
            }
        }

        ++bufferReadPos;

        CKP = 1;
    }


    //Master is requesting some data (First byte)
    else if (ReadGotAddress) {
        if (requestCallback) {
            requestCallback();
        }

        //Send some data back, specifically the first data byte
        bufferWritePos = 0;

        //Need to read otherwise it will not clear the buffer
        int temp = SSPBUF;


        //We can start sending data right away
        SSPBUF = buffer[bufferWritePos];

        CKP = 1;
    }

    //Master really wants some more data (Not the first byte)
    else if (ReadGotData) {
        //Master is still reading the packet
        if (bufferWritePos < sizeof(Packet_t)-1) {
            bufferWritePos = bufferWritePos + 1;
            SSPBUF = buffer[bufferWritePos];
        //Master is trying to read too much
        } else {
            SSPBUF = 69;
        }

        CKP = 1;
    }

    else if (ReadDone) {
    }
}

//What to do when we get JWire data from a master
void JWireOnReceive(AsyncCallback_t callbackToUse) {
    receiveCallback = callbackToUse;
}

//What to do on a JWire request from a master
void JWireOnRequest(AsyncCallback_t callbackToUse) {
    requestCallback = callbackToUse;
}

//Start a JWire session with a slave id
void JWireBegin(int id) {
    jWireEnabled = 1;

    TRISCbits.RC3 = 1;
    TRISCbits.RC4 = 1;

    //Set slave address
    SSPADD = id << 1;
    SMP = 0;

    //7Bit Slave mode with start and stop bit interrupts enabled
    SSPM0 = 0;
    SSPM1 = 1;
    SSPM2 = 1;
    SSPM3 = 1;

    SEN = 1;

    //Enable SSPN
    SSPEN = 1;
    SSPIE = 1;
}

void JWireRespond(unsigned char *msg, int len) {
    //Copy message
    memcpy(buffer, msg, len);
}