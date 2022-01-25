#ifndef FILESYSTEM_H
#define FILESYSTEM_H

void file_create(char* path);
void file_write(char* path, char* data);
void directory_create(char* path);

#endif // FILESYSTEM_H