#include "shell.h"

/**
 * _fmemset - fills memory
 * @o: pointer
 * @b: byte to fill
 * @n: amount of bytes
 * Return: pointer to the memory
 */
char *_fmemset(char *o, char b, unsigned int n)
{
	unsigned int i;

	for (i = 0; i < n; i++)
		o[i] = b;
	return (o);
}

/**
 * fsfree - frees string of chars
 * @pp: strings
 */
void fsfree(char **pp)
{
	char **y = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(y);
}

/**
 * _real_loc - reallocates memory
 * @ptr: pointer to block
 * @old_size: previous block
 * @new_size: new block
 * Return: pointer.
 */
void *_real_loc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *y;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	y = malloc(new_size);
	if (!y)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		y[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (y);
}

