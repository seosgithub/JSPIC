# jsPIC

Authors: Matt Ibarra, Seo Townsend 2013

jsPIC is a platform for the PIC18 processor that provides a javascript inspired API with 'remoting' capabilities for RPC.

*The networking architecture allows for meshing PIC's togeather.  E.g. If you have three PIC's, two linked by I2C and two linked by serial,
they will all communicate just fine within the networking framework.  jsPIC supports a lightweight search algorithm that
will find the correct PIC even if it has to route through other PIC's.

# Examples

## Blink a light every second

``` js
blink() {
  LA0 = ~LA0;
}

onSetup() {
  SetInterval(1000, blink);
}

onLoop() {
}
```

##Message an adjacent PIC over I2C slave/master (A is slave, B is master)

PIC A (Slave):
``` js
call() {
  LA0 = ~LA0;
  
  Packet_t *packet = AsyncMessage;
  unsigned char *data = packet->data;
}

onSetup() {
  TwitterSignUp("@a");
  TwitterAddWireSlave(0x4F);
  TwitterRegisterSubject("c", call);
}

onLoop() {
}
```

PIC B (Master):
``` js
call() {
  LA0 = ~LA0;
}

onSetup() {
  TwitterSignUp("@b");
  TwitterAddWireMaster();
  TwitterWireMasterAddSlave(0x4F, "@a");
  
  //Send message to A
  memcpy(message, "hello", 5);
  Tweet("@a", "c", message);
}

onLoop() {
}
```

##Message an adjacent PIC over I2C slave/master and serial (A is slave, B is master, C is serial) A <=i2c=> B <=serial=> C

PIC A (Slave):
``` js
call() {
  LA0 = ~LA0;
  
  Packet_t *packet = AsyncMessage;
  unsigned char *data = packet->data;
}

onSetup() {
  TwitterSignUp("@a");
  TwitterAddWireSlave(0x4F);
  TwitterRegisterSubject("c", call);
}

onLoop() {
}
```

PIC B (Master):
``` js
onSetup() {
  TwitterSignUp("@b");
  TwitterAddWireMaster();
  TwitterAddSerial();
  TwitterWireMasterAddSlave(0x4F, "@a");
}

onLoop() {
}
```

PIC C (Master):
``` js
call() {
  LA0 = ~LA0;
}

onSetup() {
  TwitterSignUp("@c");
  TwitterAddSerial();
  
  //Send message to A
  memcpy(message, "hello", 5);
  Tweet("@a", "c", message);
}

onLoop() {
}
```

# File Breakdown
## JWire.c - Raw I2C Slave access
## main.c - User onSetup() and onLoop() code goes here
## serial.c - Raw Serial Access
## twitter.c - IPC networking managere
## twitterSerial.c - Driver for using serial.c with Twitter
## twitterWireMaster.c - I2C Master driver for using wireMaster.c with Twitter
## twitterWireSlave.c - I2C Slave driver for using JWire.c with Twitter
## wireMaster.c - I2C Master raw access
## Async.c - Asynchronous function que
## Interurpts.c - Interrupt handler
## jspic.c - Main function that calls onSetup() and onBegin()
