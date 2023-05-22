#include "shell.h"

/**
 * *string_copy - copies astring of characters
 * @src: source
 * @dest: destination
 * @i: total characters
 * Return: new string
 */
char *string_copy(char *src, int i, char *dest)
{
	char *st = dest;
	int k, l;

	for (k = 0; (src[k] != '\0' && k < i - 1); k++)
	{
		dest[k] = src[k];
	}

	if (k < i)
	{
		l = k;

		while (l < i)
		{
			dest[k] = '\0';
			l++;
		}
	}
	return (st);
}
/**
 * *string_cat - concat function entry
 * @src: sourec
 * @dest: destination
 * @i: bytes
 * Return: new concat string
 */
char *string_cat(char *src, char *dest, int i)
{
	char *t = dest;
	int m, n;

	for (m = 0; dest[m] != '\0'; m++)
	{
		for (n = 0; (src[n] != '\0' && n < i); n++)
		{
			dest[m] = src[n];
		}
	}
	if (n < i)
		dest[m] = '\0';
	return (t);
}
/**
 * *loc - finds a character
 * @str: original string
 * @ch: search parameter
 * Return: a pointer
 */
char *loc(char *str, char ch)
{
	while (*str++ != '\0')
	{
		if (*str == ch)
		{
			return (str);
		}
	}
	return (NULL);
}
