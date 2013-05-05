#include "jspic.h"

//Motor
#if 1

//Sabertooth motor
//######################
void send(char command, char data) {
  char address = 130;
  char packet[4];
  packet[0] = address;
  packet[1] = command;
  packet[2] = data;
  packet[3] = (address + command + data) & 127;
  SerialWrite(packet, 4);
}

void go(unsigned char leftForward, unsigned char leftPower, unsigned char rightForward, unsigned char rightPower) {
  leftPower = leftPower >> 1;
  rightPower = rightPower >> 1;
  if (!leftForward) {
    send(5, leftPower);
  } else {
    send(4, leftPower);
  }
  
  if (!rightForward) {
    send(1, rightPower);
  } else {
    send(0, rightPower);
  }
}
//#######################

void ss() {
	static int leftForward = 1;
	static int rightForward = 0;
	leftForward = !leftForward;
	rightForward = !rightForward;
	go(leftForward, 0xFF, rightForward, 0xFF);
}

//m command
void onMove() {
  Packet_t *packet = (Packet_t *)AsyncMessage;
  unsigned char leftForward = packet->data[0];
  unsigned char leftPower = packet->data[1];
  unsigned char rightForward = packet->data[2];
  unsigned char rightPower = packet->data[3];
  
  go(leftForward, leftPower, rightForward, rightPower);
}

void onSetup() {
	TwitterSignUp("@m");
  TwitterAddWireSlave(0x5f);
  TwitterRegisterSubject("m", onMove);
	SerialBegin();
}

void onLoop() {
}

#endif

//Program motor
#if 0

//Sabertooth motor
//######################
void send(char command, char data) {
  char address = 130;
  char packet[4];
  packet[0] = address;
  packet[1] = command;
  packet[2] = data;
  packet[3] = (address + command + data) & 127;
  SerialWrite(packet, 4);
}

void go(unsigned char leftForward, unsigned char leftPower, unsigned char rightForward, unsigned char rightPower) {
  leftPower = leftPower >> 1;
  rightPower = rightPower >> 1;
  if (!leftForward) {
    send(5, leftPower);
  } else {
    send(4, leftPower);
  }
  
  if (!rightForward) {
    send(1, rightPower);
  } else {
    send(0, rightPower);
  }
}
//#######################

void ss() {
	static int leftForward = 1;
	static int rightForward = 0;
	leftForward = !leftForward;
	rightForward = !rightForward;
	go(leftForward, 0xFF, rightForward, 0xFF);
}

//m command
void onMove() {
  Packet_t *packet = (Packet_t *)AsyncMessage;
  unsigned char leftForward = packet->data[0];
  unsigned char leftPower = packet->data[1];
  unsigned char rightForward = packet->data[2];
  unsigned char rightPower = packet->data[3];
  
  go(leftForward, leftPower, rightForward, rightPower);
}

void onSetup() {
  SerialBegin();
  
  send(15, 3);
  go(1, 0xFF, 1, 0xFF);
}

void onLoop() {
}

#endif

//Router (Without serial, router controls motors)
#if 0
typedef struct MOTORDATA_T_ {
  unsigned char leftForward;
  unsigned char leftPower;
  unsigned char rightForward;
  unsigned char rightPower;
} MotorData_t;

void sendMotorCommand(unsigned char leftForward, unsigned char leftPower, unsigned char rightForward, unsigned char rightPower) {
  MotorData_t motorData;
  motorData.leftForward = leftForward;
  motorData.leftPower = leftPower;
  motorData.rightForward = rightForward;
  motorData.rightPower = rightPower;
  Tweet("@m", "m", &motorData);
}

void onRead() {
  Packet_t *p = AsyncMessage;
  
  if (p->data[0] == 3) {
      unsigned short distance = p->data[1] << 8 | p->data[2];
      
      if (distance > 350) {
        sendMotorCommand(1, 0xFF, 1, 0xFF); 
      } else {
        sendMotorCommand(0, 0xFF, 1, 0xFF); 
      }
  }
}

void onSetup() {
	TwitterSignUp("@r");
  TwitterAddWireMaster();
  TwitterWireMasterAddSlaveLegacy("@i", 0x4f, "@r", "r");
  TwitterWireMasterAddSlave("@m", 0x5f);
  TwitterRegisterSubject("r", onRead);
}

void onLoop() {
}

#endif

//Router (Serial passthrough)
#if 0

typedef struct MOTORDATA_T_ {
  unsigned char leftForward;
  unsigned char leftPower;
  unsigned char rightForward;
  unsigned char rightPower;
} MotorData_t;

void onSetup() {
	TwitterSignUp("@r");
   TwitterAddWireMaster();
   TwitterWireMasterAddSlaveLegacy("@i", 0x4f, "@a", "r");
  TwitterWireMasterAddSlave("@m", 0x5f);
  TwitterAddSerial();
}

void onLoop() {
}

#endif

//ARM Slave (XBEE RX)
#if 0

typedef struct MOTOR_DATA_T {
  unsigned char leftForward;
  unsigned char leftPower;
  unsigned char rightForward;
  unsigned char rightPower;
  unsigned char trash;
} MotorData_t;

void call() {
  MotorData_t motorData;
  motorData.leftForward = 1;
  motorData.leftPower = 0xFF;
  motorData.leftForward = 1;
  motorData.leftPower = 0xFF;
  Tweet("@m", "m", &motorData);
}

void onSetup() {
	TwitterSignUp("@x");
  TwitterAddSerial();
  TwitterAddWireSlave(0x4F);
  //SetInterval(40, call);
}

void onLoop() {
}

#endif