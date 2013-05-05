# jsPIC

jsPIC is a platform for the PIC18 processor that provides a javascript inspired API with 'remoting' capabilities for RPC.

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
