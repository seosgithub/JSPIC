#ifndef TWITTER_WIRE_SLAVE_H_
#define TWITTER_WIRE_SLAVE_H_

#include "jwire.h"
#include "interval.h"
#include "crashHelper.h"

void TwitterWireSlaveBegin(AsyncCallback_t twitterReceive);
void TwitterAddWireSlave(int id);
int TwitterSendWireSlave(Packet_t *packet);
void TwitterWireSlaveReset();

#endif