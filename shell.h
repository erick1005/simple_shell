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

/*shell1 prototypes */


/* allias prototypes */
int _usedcommands(info_t *input);
int _allias(info_t *input, char *strn);
int select_allias(info_t *input, char *strn);
int display_allias(list_t *node);
int _cpallias(info_t *input);

/* error_puts prototypes */
void error_puts(char *strn);
int error_char(char *r);
int puts_char(char *strn, int fd);

typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;
#endif
