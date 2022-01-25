#include "cli.h"
#include "input.h"
#include "filesystem.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void arg_template_init()
{
    cli_arg_template_add("n", "node", false, NODE);
    cli_arg_template_add("g", "git", true, GIT);
}

void execute_args()
{
    CLIArgument* git_arg = cli_get_arg(GIT);

    // Change later to support upstream
    if (git_arg != NULL) {
        system("git init");
        system(strcat("git remote add origin", git_arg->value));
    }

    if (cli_get_arg(NODE) != NULL) {
        int port;
        while (!port) {
            port = input_number("Enter a server port");
        }
       
       if (input_choice("Would you like authentication in your application", NO) == YES) {
           char* auth_options[] = { "JSON Web Token" };
           int auth_choice = input_multiple_choice("Please choose an authentication type", auth_options, sizeof(auth_options) / sizeof(char*));
           if (auth_choice == 1) {
               system("npm i jsonwebtoken");
           }
       }

       system("npm init -y");
       system("npm i express");

        directory_create("./src");
        directory_create("./routes");
        file_create("./src/index.js");
        file_write("./src/index.js", "const express = require(\"express\");\nconst app = express();\n\napp.use(express.json());\n");
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