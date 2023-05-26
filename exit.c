#include "shell.h"

/**
 **_stringcpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@z: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_stringcpy(char *dest, char *src, int z)
{
	int i, k = 0;
	char *o = dest;

	i = 0;
	while (src[i] != '\0' && i < z - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < z)
	{
		z = i;
		while (z < k)
		{
			dest[z] = '\0';
			z++;
		}
	}
	return (o);
}

/**
 **_stringcat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@z: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_stringcat(char *dest, char *src, int z)
{
	int i, k;
	char *o = dest;

	i = 0;
	k = 0;
	while (dest[i] != '\0')
		i++;
	while (src[z] != '\0' && z < k)
	{
		dest[i] = src[z];
		i++;
		z++;
	}
	if (z < i)
		dest[i] = '\0';
	return (o);
}

/**
 **stringchar - locates a character in a string
 *@o: the string to be parsed
 *@c: the character to look for
 *Return: (o) a pointer to the memory area o
 */
char *stringchar(char *o, char c)
{
	do {
		if (*o == c)
			return (o);
	} while (*o++ != '\0');

	return (NULL);
}
