#include "async.h"
#include "crashHelper.h"

#define MAX_CALLBACKS 20
#define MAX_MESSAGE_SIZE 20

typedef struct CALLBACK_INFO_T {
    AsyncCallback_t callback;
    char message[MAX_MESSAGE_SIZE];
} CallbackInfo_t;

static CallbackInfo_t callbacks[MAX_CALLBACKS];

static char *AsyncMessage = 0;

void Async(AsyncCallback_t function, unsigned char *data, int len) {
    //Find an open callback
    for (int i = 0; i < MAX_CALLBACKS; ++i) {
        if (callbacks[i].callback == NULL) {
            memcpy(callbacks[i].message, data, len);
            callbacks[i].callback = function;
            return;
        }
    }

    //No open callbacks
    Crash(7);
}

void AsyncBlank(AsyncCallback_t function) {
    Async(function, NULL, 0);
}

void AsyncTick() {
    for (int i = 0; i < MAX_CALLBACKS; ++i) {
        if (callbacks[i].callback) {
            AsyncMessage = callbacks[i].message;
            callbacks[i].callback();
            callbacks[i].callback = NULL;
            return;
        }
    }
}

void AsyncBegin() {
    for (int i = 0; i < MAX_CALLBACKS; ++i)
        callbacks[i].callback = NULL;
}