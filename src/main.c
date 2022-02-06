#include "cli.h"
#include "input.h"
#include "filesystem.h"
#include "util.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

void arg_template_init()
{
    cli_arg_template_add("n", "node", false, NODE);
    cli_arg_template_add("g", "git", true, GIT);
    cli_arg_template_add("c", "c-file", false, C_FILE);
}

void execute_args()
{
    CLIArgument* git_arg = cli_get_arg(GIT);

    // Change later to support upstream
    if (git_arg) {
        system("git init");
        system(strcat("git remote add origin", git_arg->value));
    }

    if (cli_get_arg(C_FILE)) {
        char* file_name = input_string("Enter name");

        char header_name[strlen(file_name) * sizeof(char) + 2];
        strcpy(header_name, file_name);
        strcat(header_name, ".h");

        char src_name[strlen(file_name) * sizeof(char) + 2];
        strcpy(src_name, file_name);
        strcat(src_name, ".c");

        file_create(header_name);
        file_create(src_name);

        char header_guard_def[strlen(file_name) * sizeof(char) + 2];
        strcpy(header_guard_def, file_name);

        str_replace(header_guard_def, ' ', '_');
        to_upper_case(header_guard_def);
        strcat(header_guard_def, "_H");

        char header_src[36 + (strlen(header_guard_def) * sizeof(char) * 3)];
        sprintf(header_src, "#ifndef %s\n#define %s\n\n#endif // %s", header_guard_def, header_guard_def, header_guard_def);

        file_write(header_name, header_src);

        char src_file_src[16 + (strlen(file_name) * sizeof(char))];
        sprintf(src_file_src, "#include \"%s.h\"", file_name);

        file_write(src_name, src_file_src);
        free(file_name);

        return;
    }

    if (cli_get_arg(NODE) != NULL) {
        int port = 0;
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

    //    system("npm init -y");
    //    system("npm i express");

        directory_create("./src");
        directory_create("./routes");
        // file_create("./src/index.js");
        // file_write("./src/index.js", "const express = require(\"express\");\nconst app = express();\n\napp.use(express.json());\n");

        return;
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