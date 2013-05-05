#ifndef TWITTER_WIRE_MASTER_H_
#define TWITTER_WIRE_MASTER_H_

#include "wireMaster.h"
#include "interval.h"
#include "crashHelper.h"
#include "ledCounter.h"

void TwitterWireMasterBegin(AsyncCallback_t twitterReceive);
void TwitterAddWireMaster();
int TwitterSendWireMaster(Packet_t *packet);
void TwitterWireMasterReset();

void TwitterWireMasterAddSlave(char *name, int id);
void TwitterWireMasterAddSlaveLegacy(char *name, int id, char *to, char *subject);

#endif