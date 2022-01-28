#include "cli.h"
#include "util.h"
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <stdio.h>

CLIArgumentTemplate* cli_args_template;
int args_template_len = 0;

CLIArgument* cli_args;
int args_len = 0;

int argc;
char** argv;

void cli_init(int arg_count, char** arg_vec)
{
    argc = arg_count;
    argv = arg_vec;

    cli_args_template = malloc(sizeof *cli_args_template);
    if (!cli_args_template) {
        error_malloc_failed();
    }

    cli_args = malloc(sizeof *cli_args);
    if (!cli_args) {
        error_malloc_failed();
    }

    // Remove directory argument
    argv++;
    argc--;
}

void cli_arg_template_add(char* short_hand, char* long_hand, bool has_value, CLIArgumentType type)
{
    void *new_mem = realloc(cli_args_template, sizeof *cli_args_template * (args_template_len + 1));
    if (!new_mem) {
        error_malloc_failed();
    }

    cli_args_template = new_mem;

    CLIArgumentTemplate* arg_template = cli_args_template + args_template_len++;
    arg_template->short_hand = short_hand;
    arg_template->long_hand = long_hand;
    arg_template->has_value = has_value;
    arg_template->type = type;
}

bool cli_args_parse()
{
    int arg_index = 0;
    char* current_argument;

    while (arg_index < argc) {
        current_argument = argv[arg_index];

        char first_two_chars[2];
        strncpy(first_two_chars, current_argument, 2);
        if (current_argument[0] != '-' && (strcmp(first_two_chars, "--") != 0)) {
            printf("[PARSING ERROR]: Invalid argument '%s'. Argument must begin with dashses.", current_argument);
            return false;
        }

        CLIArgument* argument = NULL;

        for (int i = 0; i < args_template_len; i++) {
            CLIArgumentTemplate template = cli_args_template[i];
            char* argument_stripped = current_argument;
            if (strcmp(++argument_stripped, template.short_hand) != 0 && strcmp(++argument_stripped, template.long_hand) != 0) continue;

            argument = malloc(sizeof *argument);
            if (!argument) {
                error_malloc_failed();
            }

            argument->type = template.type;
            
            if (template.has_value) {
                if (++arg_index >= argc) {
                    printf("[PARSING ERROR]: Could not find value for argument '%s'.", current_argument);
                    return false;
                }

                char* next_word = argv[++arg_index];
                argument->value = next_word;
            }

            break;
        }

        if (!argument) {
            printf("[PARSING ERROR]: Unrecognised argument '%s'.", current_argument);
            return false;
        }

        cli_args = realloc(cli_args, sizeof *cli_args * (args_len + 1));
        if (!cli_args) {
            error_malloc_failed();
        }

        args_len++;
        cli_args[args_len - 1] = *argument;
        arg_index++;     
    }

    return true;
}

CLIArgument* cli_get_arg(CLIArgumentType type)
{
    for (int i = 0; i < args_len; i++) {
        if (cli_args[i].type == type) {
            return &cli_args[i];
        }
    }

    return NULL;
}