#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_

#include <xc.h>
#include "interval.h"
#include "serial.h"
#include "jwire.h"
#include "wireMaster.h"
#include "crashHelper.h"
#include "flipper.h"

interrupt void onInterrupt();

#endif