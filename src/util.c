#include "util.h"
#include <string.h>
#include <ctype.h>

void to_lower_case(char* str)
{
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}