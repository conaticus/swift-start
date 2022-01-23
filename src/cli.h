#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

typedef enum
{
    NODE,
    GIT,
} CLIArgumentType;

typedef struct
{
    char* short_hand;
    char* long_hand;
    bool has_value;
    CLIArgumentType type;
} CLIArgumentTemplate;

typedef struct 
{
    CLIArgumentType type;
    char* value;
} CLIArgument;

extern CLIArgumentTemplate* cli_args_template;
extern CLIArgument* cli_args;

void cli_init(int argc, char** argv);
void cli_arg_template_add(char* short_hand, char* long_hand, bool has_value, CLIArgumentType type);
bool cli_args_parse();
CLIArgument* cli_get_arg(CLIArgumentType type);

#endif // CLI_H