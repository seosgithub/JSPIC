#ifndef TWITTER_H_
#define TWITTER_H_

#include "async.h"
#include "json.h"
#include "crashHelper.h"
#include "jwire.h"
#include "wireMaster.h"
#include "serial.h"
#include "interval.h"
#include "flipper.h"
#include "twitterSerial.h"
#include "twitterWireMaster.h"
#include "parity.h"
#include "twitterWireSlave.h"

//Register as a twitter user
void TwitterSignUp(char *name);

//Send a message
void Tweet(char *to, char *subject, unsigned char *data);
void TweetReturn(char *data);

//What to do when we receive a certain hashtag or subject
void TwitterRegisterSubject(char *subject, AsyncCallback_t callback);

//Call this when receiving a mesasge from some interface
void TwitterOnReceive();

#endif