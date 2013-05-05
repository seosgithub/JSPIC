#include "twitterSerial.h"

static int enabled = 1;
static int used = 0;
AsyncCallback_t twitterReceive;

#define MAX_TRASH_SIZE 50
static char IncommingBuffer[MAX_TRASH_SIZE];
static char *currentIncomming = IncommingBuffer;

void TwitterSerialOnReceive() {
	enabled = 0;
	twitterReceive();
}

void TwitterSerialOnInterrupt() {
		//Insert
		*currentIncomming = *AsyncMessage;

		//Increment
		++currentIncomming;

		if (currentIncomming - IncommingBuffer > MAX_TRASH_SIZE)
			currentIncomming = IncommingBuffer;


		if (currentIncomming - IncommingBuffer >= sizeof(Packet_t)) {
			static char count = 0;
			Count(count);
			++count;
    	if (CheckParity(currentIncomming - sizeof(Packet_t))) {
				Async(TwitterSerialOnReceive, currentIncomming - sizeof(Packet_t), sizeof(Packet_t));
				currentIncomming = IncommingBuffer;
      }
		}
}

void TwitterSerialBegin(AsyncCallback_t _twitterReceive) {
	twitterReceive = _twitterReceive;
}

void TwitterAddSerial() {
	used = 1;
	SerialBegin();
	OnSerial(TwitterSerialOnInterrupt);
}

int TwitterSendSerial(Packet_t *packet) {
	if (enabled && used) {
		SerialWrite(packet, sizeof(Packet_t));
	}

	return 1;
}

void TwitterSerialReset() {
	enabled = 1;
}
