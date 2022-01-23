#include "input.h"
#include "util.h"
#include <stdio.h>
#include <string.h>

int input_multiple_choice(char* message, char* options[], int options_length)
{
    printf("%s:\n", message);

    for (int i = 0; i < options_length; i++) {
        printf("%d. %s\n", i + 1, options[i]);
    }

    printf("\nChoice: ");

    int choice;
    scanf("%d", &choice);

    if (choice > options_length || choice < 1) {
        printf("[ERROR]: Input must be a number and displayed in the given options.");
        return -1;
    }

    return choice;
}

YesOrNo input_choice(char* message, YesOrNo default_choice)
{
    if (default_choice == YES) {
        printf("%s (Y\\n): ", message);
    } else {
        printf("%s (y\\N): ", message);
    }

    char choice[3];
    gets(choice);

    to_lower_case(choice);

    if (strcmp(choice, "y") == 0 || strcmp(choice, "yes") == 0) {
        return YES;
    } else if (strcmp(choice, "n") == 0 || strcmp(choice, "no") == 0) {
        return NO;
    }

    return default_choice;
}