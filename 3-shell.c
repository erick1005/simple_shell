#include "shell.h"

/**
 * cmyenv - current environmt
 * @info: variable struct.
 * Return: 0 for success
 */
int cmyenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getenva - environmt variable
 * @info: argument struct.
 * @name:input
 * Return: pointer
 */
char *getenva(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *q;

	while (node)
	{
		q = starts_with(node->str, name);
		if (q && *q)
			return (q);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenvi -  customized variable
 * @info: struct arguments.
 *  Return: Always 0 success
 */
int mysetenvi(info_t *info)
{
	if (info->argc != 3)
	{
		_eputsd("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenvmd(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _dmyunsetenv - deletes variable
 * @info: argument struct.
 * Return: success 0
 */
int _dmyunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputsd("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_rmunsetenv(info, info->argv[i]);

	return (0);
}

/**
 * populate_envlist - entry
 * @info: argument structure
 * Return: 0 for success
 */
int populate_envlist(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		addnode_end(&node, environ[i], 0);

	info->env = node;
	return (0);
}
