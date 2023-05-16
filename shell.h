#ifndef SHELL_H
#define SHELL_H

/* all the prototypes structs or headers here*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>

#define BUFFER_SIZE 1024

void commandExec( char* line);

#endif
