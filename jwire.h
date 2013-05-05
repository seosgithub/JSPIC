#ifndef JWIRE_H_
#define JWIRE_H_

#include <xc.h>
#include "async.h"
#include "macaw.h"
#include "packets.h"
#include "crashHelper.h"

extern int jWireEnabled;

//Got an I2C interrupt
void JWireOnInterrupt();

//What to do when we get JWire data from a master
void JWireOnReceive(AsyncCallback_t callback);

//What to do on a JWire request from a master
void JWireOnRequest(AsyncCallback_t callback);

//Start a JWire session with a slave id
void JWireBegin(int id);

//Write JWire data back to a master device
void JWireRespond(unsigned char *msg, int len);

#endif