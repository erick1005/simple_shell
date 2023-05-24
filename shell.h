#ifndef SHELL_H
#define SHELL_H

/* all the prototypes structs or headers here*/

#include<stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <limits.h>
#include <errno.h>

/* read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/*command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* for convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096




typedef struct list_s {
	char *str;
	struct list_s *next;
} list_i;

typedef struct info_s {
	list_i *en;
	int argc;
	char **argv;
} info_i;

typedef struct liststr
{
        int num;
        char *str;
        struct liststr *next;
} list_t;

typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buf; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buf_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

int inter(info_t *struc);
int checker(char e, char *check);
int alpha(int e);
int conver(char *s);
int shell_main(void);

/* toem_environ.c */
char *getenvi(info_t *, const char *);
int myenvi(info_t *);
int mysetenvi(info_t *);
int _myunsetenvi(info_t *);
int pplte_env_list(info_t *);



/*exit */
char *string_copy(char *src, int i, char *dest);
char *string_cat(char *src, char *dest, int i);
char *loc(char *str, char ch);

/* getline*/
ssize_t get_line(char **linep, size_t *t, int fd);

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

/* err1 */
int erratoi(char *);
void print_errr(info_t *, char *);
int print_d(int, int);
char *convert_num(long int, int, int);
void remove_comments(char *);
int _putchar(char c);
int _eputchar(char c);
void _eputs(const char *str);

/* gtline */
ssize_t getinput(info_t *);
int get_input_line(info_t *, char **, size_t *);
void sigint_Handler(int);

#endif
