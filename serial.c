#include "serial.h"

#define MAX_MESSAGE_SIZE 20

//Buffer to store serial data
static char bufferSerial[MAX_MESSAGE_SIZE];
static int bufferPosition = 0;

//Default handler (Use SetSerialHandler to actually do something)
static AsyncCallback_t callback = 0;

void OnSerialInterrupt() {
    static char data;
    data = RCREG;

    //Error
    if (OERR) {
        CREN = 0;
        CREN = 1;
        return;
    }

    if (FERR)
        data = RCREG;

    if (callback) {
        *AsyncMessage = data;
        callback();
    }
}

void SerialBegin() {
    //Inital setup
    SPEN = 1;
    TRISCbits.RC7 = 1;
    TRISCbits.RC6 = 1;

    //Configure transmission
    TX9 = 0;
    TXEN = 1;
    SYNC = 0;
    SENDB = 1;

    //Configure receiving
    CREN = 1;

    //Configure baud-rate to 57kbits/s
    BRGH = 0;
    BRG16 = 1;
    //SPBRG = 25; //19200
    SPBRG = 51; //9600

    //Enable interrupts
    TXIE = 0;
    RCIE = 1;
}

void OnSerial(AsyncCallback_t callbackToUse) {
    //Set callback
    callback = callbackToUse;
}

//Called by the main interrupt handler to write serial requests byte by byte
char writeBuffer[100];
static int writeBufferPosition = 0; //What position are we currently reading
static int writeBufferPositionOpen = 0; //What position are we currently writing
static int isDoneTransmitting = 0;

void SerialWrite(unsigned char *data, int len) {
    //Just started
    if (writeBufferPositionOpen == 0) {
        memcpy(writeBuffer, data, len);
        writeBufferPositionOpen = len;
    } else {
        memcpy(writeBuffer+writeBufferPositionOpen, data, len);
        writeBufferPositionOpen += len;
    }
 
    //Start a serial write request
    TXIE = 1;
    isDoneTransmitting = 0;
}

void SerialWriteInterrupt() {
    if (isDoneTransmitting) {
        TXIE = 0;
        return;
    }

    //Done transmitting
    if (writeBufferPosition == writeBufferPositionOpen-1) {
        TXREG = writeBuffer[writeBufferPosition];
        writeBufferPosition = 0;
        writeBufferPositionOpen = 0;
        isDoneTransmitting = 1;
   //Just write
   } else {
        TXREG = writeBuffer[writeBufferPosition];
        ++writeBufferPosition;
    }
}
