#include "filesystem.h"
#include <stdio.h>
#include <sys/stat.h>
#include <sys/types.h>

void file_create(char* path)
{
    FILE* file_ptr = fopen(path, "w");
    fclose(file_ptr);
}

void file_write(char* path, char* data)
{
    FILE *file_ptr = fopen(path, "w");
    fprintf(file_ptr, "%s", data);
    fclose(file_ptr);
}

void directory_create(char* path)
{
    mkdir(path, 0644);
}