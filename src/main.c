#include "cli.h"
#include "input.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

void arg_template_init()
{
    cli_arg_template_add("n", "node", false, NODE);
}

void execute_args()
{
    if (cli_get_arg(NODE)) {
        /*
            Would you like authentication (y/N): 
                Please choose an authentication type:
                    1. JSON Web Token

                Enter type:
        */

       if (input_choice("Would you like authentication in your application", NO) == YES) {
           char* auth_options[] = { "JSON Web Token" };
           int auth_choice = input_multiple_choice("Please choose an authentication type", auth_options, sizeof(auth_options) / sizeof(char*));
           if (auth_choice == 1) {
               system("npm i jsonwebtoken");
           }
       }

       system("npm init -y");
       system("npm i express");
    }
}

int main(int argc, char** argv)
{
    cli_init(argc, argv);
    arg_template_init();

    if (cli_args_parse(argc, argv) == false) {
        return -1;
    }

    execute_args();
}