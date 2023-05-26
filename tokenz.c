#include "shell.h"

/**
 * **strtow - splits a string into words
 * @str: the input
 * @d: the delimeter
 * Return: a pointer
 */

char **strtow(char *str, char *d)
{
	int i, n, b, y, numwords = 0;
	char **o;

	if (str == NULL || str[0] == 0)
		return (NULL);
	if (!d)
		d = " ";
	for (i = 0; str[i] != '\0'; i++)
		if (!is_delim(str[i], d) && (is_delim(str[i + 1], d) || !str[i + 1]))
			numwords++;

	if (numwords == 0)
		return (NULL);
	o = malloc((1 + numwords) * sizeof(char *));
	if (!o)
		return (NULL);
	for (i = 0, n = 0; n < numwords; n++)
	{
		while (is_delim(str[i], d))
			i++;
		b = 0;
		while (!is_delim(str[i + b], d) && str[i + b])
			b++;
		o[n] = malloc((b + 1) * sizeof(char));
		if (!o[n])
		{
			for (b = 0; b < n; b++)
				free(o[b]);
			free(o);
			return (NULL);
		}
		for (y = 0; y < b; y++)
			o[n][y] = str[i++];
		o[n][y] = 0;
	}
	o[n] = NULL;
	return (o);
}

/**
 * **stritow2 - splits string
 * @str: input
 * @d: delimeter
 * Return: a pointer
 */
char **stritow2(char *str, char d)
{
	int i, n, b, y, numwords = 0;
	char **o;

	if (str == NULL || str[0] == 0)
		return (NULL);
	for (i = 0; str[i] != '\0'; i++)
		if ((str[i] != d && str[i + 1] == d) ||
				    (str[i] != d && !str[i + 1]) || str[i + 1] == d)
			numwords++;
	if (numwords == 0)
		return (NULL);
	o = malloc((1 + numwords) * sizeof(char *));
	if (!o)
		return (NULL);
	for (i = 0, n = 0; n < numwords; n++)
	{
		while (str[i] == d && str[i] != d)
			i++;
		b = 0;
		while (str[i + b] != d && str[i + b] && str[i + b] != d)
			b++;
		o[n] = malloc((b + 1) * sizeof(char));
		if (!o[n])
		{
			for (b = 0; b < n; b++)
				free(o[b]);
			free(o);
			return (NULL);
		}
		for (y = 0; y < b; y++)
			o[n][y] = str[i++];
		o[n][y] = 0;
	}
	o[n] = NULL;
	return (o);
}

