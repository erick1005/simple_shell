#include "shell.h"

/**
 * error_puts - displays a string of characters
 * @strn: src string
 * Return: void
 */
void error_puts(char *strn)
{
	int j = 0;

	if (strn == NULL)
		return;

	while (strn[j] != '\0')
	{
		error_char(strn[j]);
		j++;
	}
}

/**
 * error_char - inputs char to standard error
 * @r: src character
 * Return: 0 success -1 otherwise
 */
int error_char(char *r)
{
	int i;
	char buf[WRITE_BUF_SIZE];

	if (r == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (r != BUF_FLUSH)
		buf[i++] = r;
	return (0);
}

/**
 * puts_char - entry
 * @strn: src string
 * @fd: filedescriptor
 * Return: string of chars total
 */
int puts_char(char *strn, int fd)
{
	int k = 0;

	if (strn == NULL)
	{
		return (0);
	}
	while (*strn)
	{
		k = k + (puts_char(*strn++, fd));
	}
	return (k);
}
