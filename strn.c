#include "shell.h"

/**
 * _strlen - returns string length
 * @o: string to check
 * Return: integer length
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
 * _stricmp - lexicogarphic comparers two strangs.
 * @o: first
 * @s2: second
 * Return: int
 */
int _stricmp(char *o, char *s2)
{
	while (*o && *s2)
	{
		if (*o != *s2)
			return (*o - *s2);
		o++;
		s2++;
	}
	if (*o == *s2)
		return (0);
	else
		return (*o < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if begins with haystack
 * @haystack: string search
 * @needle: the substring
 * Return: address
 */
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strngcat - concatenates strings
 * @dest: destination
 * @src: source
 *
 * Return: pointer
 */
char *_strngcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}

