#include "shell.h"

/**
 * b_free - frees mem address
 * @ptr: pointer to free
 * Return: 1, otherwise 0.
 */
int b_free(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}

