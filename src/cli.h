#ifndef CLI_H
#define CLI_H

#include <stdbool.h>

typedef enum
{
    NODE,
    GIT,
    C_FILE,
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

// Gets arguments & initialises variables where required
void cli_init(int argc, char** argv);

// Add a cli argument template which is used by the parser
void cli_arg_template_add(char* short_hand, char* long_hand, bool has_value, CLIArgumentType type);

// Parses the arguments provided in argv and adds them to cli_args
bool cli_args_parse();

// Returns an argument if exists
CLIArgument* cli_get_arg(CLIArgumentType type);

#endif // CLI_H