#ifndef PACKET_H_
#define PACKET_H_

//Older packet definition
typedef struct LEGACY_PACKET_T {
    unsigned char id;
    unsigned char num;
    unsigned char parity;
    unsigned char count;
    unsigned char data[4];
} LegacyPacket_t;

//How much data?
#define PAYLOAD_LEN 5

//Newer twitter-compatible packets
typedef struct PACKET_T {
    short to;
    short from;
    unsigned char parity;
    unsigned char count;
    unsigned char subject;
    unsigned char data[PAYLOAD_LEN];
} Packet_t;

//Reveals to and from fields as two indexable bytes
typedef struct PACKETAlt_T {
    char to[2];
    char from[2];
    unsigned char parity;
    unsigned char count;
    unsigned char subject;
    unsigned char data[PAYLOAD_LEN];
} PacketAlt_t;

#endif