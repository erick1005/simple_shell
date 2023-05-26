#include "shell.h"

/**
 * _strlen - returns the length of a string
 * @o: the string whose length to check
 *
 * Return: integer length of string
 */
int _strlen(char *o)
{
	int i = 0;

	if (!o)
		return (0);

	while (*o++)
		i++;
	return (i);
}

/**
 * _strcmp - performs lexicogarphic comparison of two strangs.
 * @fs1: the first strang
 * @ss2: the second strang
 *
 * Return: negative if fs1 < s2, positive if fs1 > s2, zero if fs1 == s2
 */
int _strcmp(char *fs1, char *s2)
{
	while (*fs1 && *s2)
	{
		if (*fs1 != *s2)
			return (*fs1 - *s2);
		fs1++;
		s2++;
	}
	if (*fs1 == *s2)
		return (0);
	else
		return ((*fs1 < *s2) ? -1 : 1);
}

/**
 * startswith - checks if needle starts with haystack
 * @haystack: string to search
 * @needle: the substring to find
 *
 * Return: address of next char of haystack or NULL
 */
char *startswith(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: the destination buffer
 * @src: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}
