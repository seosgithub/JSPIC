#include "parity.h"

unsigned char GetParity(Packet_t *packet) {
	PacketAlt_t *p = (PacketAlt_t *)packet;

	unsigned char parity = p->to[0] + p->to[1] + p->from[0] + p->from[1];

	return parity;
}

void SetParity(Packet_t *packet) {
	packet->parity = GetParity(packet);
}

int CheckParity(Packet_t *packet) {
	return (packet->parity == GetParity(packet));
}
