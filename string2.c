#include "string2.h"

void strcpy2(char *dest, const char *loc) {
    if (loc == NULL)
        return;
    
    while (*loc) {
        *dest = *loc;
        ++dest;
        ++loc;
    }

    *dest = 0;
}