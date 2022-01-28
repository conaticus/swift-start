#ifndef INPUT_H
#define INPUT_H

#include <stdbool.h>

typedef enum
{
    YES,
    NO
} YesOrNo;

YesOrNo input_choice(char* message, YesOrNo default_choice);
int input_multiple_choice(char* message, char* options[], int options_length);
char* input_string(char* message);
int input_number(char* message);

#endif // INPUT_H