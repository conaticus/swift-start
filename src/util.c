#include "util.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void to_lower_case(char* str)
{
    for (int i = 0; i < strlen(str); i++) {
        str[i] = tolower(str[i]);
    }
}

void to_upper_case(char* str)
{
    for (int i = 0; i < strlen(str); i++) {
        str[i] = toupper(str[i]);
    }
}

void str_replace(char* str, char char_a, char char_b)
{
    for (int i = 0; i < strlen(str); i++) {
        if (str[i] == char_a) str[i] = char_b;
    }
}

void error_malloc_failed()
{
    printf("[MEMORY ERROR]: Failed to allocate memory");
    exit(-1);
}