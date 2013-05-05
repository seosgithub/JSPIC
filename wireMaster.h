#ifndef WIRE_MASTER_H_
#define WIRE_MASTER_H_

#include "async.h"
#include "flipper.h"
#include "packets.h"

extern int wireMasterEnabled;
extern unsigned char *LegacyData;

void WireSend(int deviceId, unsigned char *data, int len, AsyncCallback_t callback);

//Data and info encoded as json (AsyncMessage) { data: message }
void WireGetString(int address, AsyncCallback_t callback);

//Get data in a legacy binary format
void WireGetLegacy(int address, int len, AsyncCallback_t callback);

//Setup I2C master mode
void WireBegin();

//Caled when SSPIF is enabled
void WireOnInterrupt();

#endif