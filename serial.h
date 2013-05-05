#ifndef SERIAL_H_
#define SERIAL_H_

#include <xc.h>
#include "async.h"
#include "crashHelper.h"
#include "packets.h"
#include "ledCounter.h"

//Called on the actual serial interrupt (Individual bytes)
void OnSerialInterrupt();

//Configure the serial callback
void OnSerial(AsyncCallback_t callback);

//Start serial
void SerialBegin();

//Write to serial
void SerialWrite(char *data, int len);

//Interrupt handler for writing byte by byte
void SerialWriteInterrupt();

#endif