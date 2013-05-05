#include "twitterWireMaster.h"

static int enabled = 1;
static int used = 0;
AsyncCallback_t twitterReceive;
typedef struct SLAVE_T {
	short name;
	int id;
	char isLegacy;
	short legacyTo;
	char subject;
} Slave_t;

static Slave_t slaveA;
static Slave_t slaveB;

void TwitterWireMasterAddSlave(char *name, int id) {
	if (slaveA.id == 0) {
		memcpy(&slaveA.name, name, 2);
		slaveA.id = id;
		slaveA.isLegacy = 0;
	} else if (slaveB.id == 0) {
		memcpy(&slaveB.name, name, 2);
		slaveB.id = id;
		slaveB.isLegacy = 0;
	}
}

void TwitterWireMasterAddSlaveLegacy(char *name, int id, char *to, char *subject) {
	if (slaveA.id == 0) {
		memcpy(&slaveA.name, name, 2);
		slaveA.id = id;
		slaveA.isLegacy = 1;
		memcpy(&slaveA.legacyTo, to, 2);
		slaveA.subject = subject[0];
	} else if (slaveB.id == 0) {
		memcpy(&slaveB.name, name, 2);
		slaveB.id = id;
		slaveA.isLegacy = 1;
		memcpy(&slaveB.legacyTo, to, 2);
		slaveB.subject = subject[0];
	}
}

void TwitterWireMasterBegin(AsyncCallback_t _twitterReceive) {
	twitterReceive = _twitterReceive;
	slaveA.id = 0;
	slaveB.id = 0;
}

void PollCallback() {
}

//Richards IR hack
unsigned char irDownConvert(short input) {
  
}

void PollCallbackLegacyA() {
	LegacyPacket_t copy = *(LegacyPacket_t *)AsyncMessage;
	Packet_t *packet = (Packet_t *)AsyncMessage;
	packet->to = slaveA.legacyTo;
	packet->from = slaveA.name;
	packet->parity = copy.parity;
	packet->count = copy.count;
	packet->data[0] = copy.num;
	packet->subject = slaveA.subject;
	packet->data[1] = copy.data[0];
	packet->data[2] = copy.data[1];
	packet->data[3] = copy.data[2];
	packet->data[4] = copy.data[3];

  if (copy.num != 0)
	  twitterReceive();
}

void PollCallbackLegacyB() {
	LegacyPacket_t copy = *(LegacyPacket_t *)AsyncMessage;
}

void PollSlaves() {
	if (slaveA.id) {
		if (slaveA.isLegacy)
			WireGetLegacy(slaveA.id, sizeof(LegacyPacket_t), PollCallbackLegacyA);
	}

	if (slaveB.id) {
		if (slaveB.isLegacy)
			WireGetLegacy(slaveB.id, sizeof(LegacyPacket_t), PollCallbackLegacyB);
	}
}

void TwitterAddWireMaster() {
	used = 1;
	WireBegin();
	SetInterval(100, PollSlaves);
}

int TwitterSendWireMaster(Packet_t *packet) {
	if (enabled && used) {
		//Check if matching ID was found
		short name = packet->to;

		if (name == slaveA.name) {
			WireSend(slaveA.id, packet, sizeof(Packet_t), NULL);
		} else if (name == slaveB.name) {
			WireSend(slaveB.id, packet, sizeof(Packet_t), NULL);
		}
	}

	return 1;
}

void TwitterWireMasterReset() {
	enabled = 1;
}
