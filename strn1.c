#include "shell.h"

/**
 * _stricpy - copies a string
 * @dest: destination
 * @src: source
 * Return: pointer
 */
char *_stricpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _stridup - duplicates a string
 * @str: src string
 * Return: pointer
 */
char *_stridup(const char *str)
{
	int length = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		length++;
	ret = malloc(sizeof(char) * (length + 1));
	if (!ret)
		return (NULL);
	for (length++; length--;)
		ret[length] = *--str;
	return (ret);
}

/**
 * _putspr - prints string
 * @str: chars
 * Return: Nothing
 */
void _putspr(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchars(str[i]);
		i++;
	}
}

/**
 * _putchars - writes r to stdout
 * @r: character output
 * Return: On success 1. -1 otherwise
 */
int _putchars(char r)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (r == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (r != BUF_FLUSH)
		buf[i++] = r;
	return (1);
}

