#ifndef JSON_H_
#define JSON_H_

#include "string2.h"
#include "flipper.h"

void JsonNew(char* string);     // Add braces; basically, the object you are
// going to add your data too.

void JsonSetString(char* input, char* key, char* string);
void JsonSetValue(char* input, char* key, int value);

int JsonGetString(char* input, char* key, char* string);
int JsonGetValue(char* input, char* key);
#endif