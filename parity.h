#ifndef PARITY_H_
#define PARITY_H_

#include "packets.h"

//Sets a packets parity
void SetParity(Packet_t *packet);

//Checks a packets parity
int CheckParity(Packet_t *packet);

#endif