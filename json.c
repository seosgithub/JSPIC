//
//  json.c
//  learningStrings
//
//  Created by Matthew Ibarra on 4/6/13.
//  Copyright (c) 2013 Matthew Ibarra. All rights reserved.
//

#include <stdio.h>


#include "json.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define COLON_SPACE ": "

#define MAX_STRING_SIZE 150

static char result[MAX_STRING_SIZE];  // Shouldn't need more than 200

void JsonNew(char* string) {
    sprintf(string, "");
}

int JsonGetValue(char* input, char* key) {
    //Find the key
    char* substr_s = strstr(input, key);

    int length_key = strlen(key);
    substr_s = substr_s + length_key + 1;   //Removes the semi-colon
    //Pointing at 'value' now
    //At the value
    if(substr_s != NULL) {
        //After value
        for(int i = 0; substr_s[i] != '\n'; ++i) {
            result[i] = substr_s[i];
            result[i+1] = 0;
        }

        return atoi(result);
    }
    return 666;
}


void JsonSetString(char* input, char* key, char* str) {
    int len = strlen(input);
    sprintf(input+len, "%s:%s\n", key, str);
}

void JsonSetValue(char* input, char* key, int value) {
    int len = strlen(input);
    sprintf(input+len, "%s:%d\n", key, value);
}


int JsonGetString(char* input, char* key, char* string) {
    //Find the key
    char* substr_s = strstr(input, key);

    int length_key = strlen(key);
    substr_s = substr_s + length_key + 1;   //Removes the semi-colon
    //Pointing at 'string' now

    //At the string
    if(substr_s != NULL) {
        //After value
        for(int i = 0; substr_s[i] != '\n'; ++i) {
            string[i] = substr_s[i];
            string[i+1] = 0;
        }
        
        return 0;
    }
    return -1;
}