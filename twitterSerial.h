#ifndef TWITTER_SERIAL_H_
#define TWITTER_SERIAL_H_

#include "interval.h"
#include "serial.h"
#include "parity.h"
#include "ledCounter.h"

void TwitterSerialBegin(AsyncCallback_t twitterReceive);
void TwitterAddSerial();
int TwitterSendSerial(Packet_t *packet);
void TwitterSerialReset();

#endif