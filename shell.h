#ifndef SHELL_H
#define SHELL_H

/* all the prototypes structs or headers here*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stddef.h>

#define BUFFER_SIZE 1024

typedef struct info_s {
        int readfd;
} info_t;

int inter(info_t *struc);
int checker(char e, char *check);
int alpha(int e);
int conver(char *s);

#endif
