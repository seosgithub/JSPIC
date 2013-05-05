#ifndef ASYNC_H_
#define ASYNC_H_

#include "globals.h"
#include "string2.h"

extern char *AsyncMessage; //Stores the async data
typedef void (*AsyncCallback_t)();

//Run this before using Async
void AsyncBegin();

//Que a function asynchronously
void Async(AsyncCallback_t callback, unsigned char *data, int len);
void AsyncBlank(AsyncCallback_t callback); //Without data

//Main program loop should call this (Main event loop)
void AsyncTick();

#endif