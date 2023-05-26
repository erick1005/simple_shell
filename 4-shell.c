#include "shell.h"

/**
 * _eputsd - displays characters
 * @str: input
 * Return: void
 */
void _eputsd(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		eputchar(str[i]);
		i++;	}
}

/**
 *eputchar - displays char r to stderr
 * @r: input
 * Return: success 1.
 */
int eputchar(char r)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (r == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (r != BUF_FLUSH)
		buf[i++] = r;
	return (1);
}

/**
 * put_fd - entry
 * @r: character to print
 * @fd: filedescriptor
 * Return: success 1.
 */
int put_fd(char r, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (r == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (r != BUF_FLUSH)
		buf[i++] = r;
	return (1);
}

/**
 * _edputsfd - display input string
 * @str: input
 * @fd: filedescriptor
 * Return: int
 */
int _edputsfd(char *str, int fd)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += put_fd(*str++, fd);
	}
	return (i);
}
