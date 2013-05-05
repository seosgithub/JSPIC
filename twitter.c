#include "twitter.h"

//My name
static unsigned short name;

//Subjects
typedef struct SUBJECT_T {
	char subject;
	AsyncCallback_t callback;
} Subject_t;
static Subject_t subjectA;
static Subject_t subjectB;

void TwitterSignUp(char *_name) {
	memcpy(&name, _name, 2);

	TwitterSerialBegin(TwitterOnReceive);
	TwitterWireMasterBegin(TwitterOnReceive);
	TwitterWireSlaveBegin(TwitterOnReceive);

	subjectA.callback = 0;
	subjectB.callback = 0;
}

//Should we watch for a loopback condition?
void Send(Packet_t *packet) {
	SetParity(packet);
	//0 - Will reach host
	//1 - Not sure if it will reach host
	TwitterSendWireMaster(packet) && TwitterSendWireSlave(packet) && TwitterSendSerial(packet);	
}

void Tweet(char *to, char *subject, unsigned char *data) {
	//Create packet
	Packet_t packet;
	memcpy(&packet.to, to, 2);
	memcpy(&packet.from, &name, 2);
	packet.subject = subject[0];
	memcpy(packet.data, data, PAYLOAD_LEN);

	Send(&packet);
}

void TweetReturn(char *data) {

}


void TwitterRegisterSubject(char *_subject, AsyncCallback_t callback) {
	char subject = _subject[0];

	if (!subjectA.callback) {
		subjectA.callback = callback;
		subjectA.subject = subject;
	} else if (!subjectB.callback) {
		subjectB.callback = callback;
		subjectB.subject = subject;
	}
}

void HandleMention() {
	Packet_t *packet = AsyncMessage;

	//Is this to me?
	if (packet->to == name) {
		//Matches a subject?
		if (subjectA.callback && subjectA.subject == packet->subject) {
			Async(subjectA.callback, AsyncMessage, sizeof(Packet_t));
		} else if (subjectB.callback && subjectB.subject == packet->subject) {
			Async(subjectB.callback, AsyncMessage, sizeof(Packet_t));	
		}
	//Forward
	} else {
		Send(packet);
	}
} 

void HandleHashtag() {
	Packet_t *packet = AsyncMessage;
}

//Re-enable interface for transmission
void ResetAllInterfaces() {
	TwitterSerialReset();
	TwitterWireMasterReset();
	TwitterWireSlaveReset();
}

void TwitterOnReceive() {
	PacketAlt_t *packet = AsyncMessage;

	//Decode start of packet
	if (packet->to[0] == '@')
		HandleMention();
	else if (packet->to[0] == '#')
		HandleHashtag();

	ResetAllInterfaces();
}
