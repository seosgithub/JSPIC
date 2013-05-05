#ifndef INTERVAL_H_
#define INTERVAL_H_

#include <xc.h>
#include "async.h"

//Called on the actual interval interrupt
void OnIntervalInterrupt();

//Configure the serial callback
void SetInterval(int milliseconds, void (*callbackToUse)());

#endif