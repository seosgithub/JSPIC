#include "twitterWireSlave.h"

static int enabled = 1;
static int used = 0;
AsyncCallback_t twitterReceive;

void TwitterWireSlaveOnReceive() {
	enabled = 0;
	twitterReceive();
}

void TwitterWireSlaveBegin(AsyncCallback_t _twitterReceive) {
	twitterReceive = _twitterReceive;
}

static int hasRequest = 0;
static Packet_t request;

void OnRequest() {
	if (hasRequest) {
		JWireRespond(&request, sizeof(Packet_t));
	} else {
		request.to = 0;
		JWireRespond(&request, sizeof(Packet_t));
	}

	hasRequest = 0;
}

void OnReceive() {
	enabled = 0;
	twitterReceive();
}

void TwitterAddWireSlave(int id) {
	used = 1;
	JWireBegin(id);
	JWireOnRequest(OnRequest);
	JWireOnReceive(OnReceive);
}

int TwitterSendWireSlave(Packet_t *packet) {
	if (enabled && used) {
		memcpy(&request, packet, sizeof(Packet_t));
		hasRequest = 1;
	}

	return 1;
}

void TwitterWireSlaveReset() {
	enabled = 1;
}
