#include "shell.h"
#include <stdlib.h>

void print_list_str(char **list);
char *starts_with(const char *str, const char *prefix);
int _unsetenv(info_t *info, const char *name);
list_t *add_node_end(list_t **head, char *str, int len);


/**
 * myenvi - prints  current environment
 * @info:  containing potential arguments.
 * Return: Always 0
 */
int myenvi(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * getenvi - gets the value  environ variable
 * @info: Structure contains potential arguments.
 * @name: env var name
 *
 * Return: the value
 */
char *getenvi(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *p;

	while (node)
	{
		p = starts_with(node->str, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * mysetenvi - Initialize a new environment variable,
 *             or modify an existing one
 * @info: contain potential arguments.
 *  Return: Always 0
 */
int mysetenvi(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (setenv(info, info->argv[1], info->argv[2], 1) != 0)
		return (0);
	return (1);
}

/**
 * _myunsetenvi - Remove  environment variable
 * @info:  contain potential arguments. Used to maintain
 *        constant function prototype.
 * Return: Always 0
 */
int _myunsetenvi(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
		_unsetenv(info, info->argv[i]);

	return (0);
}

/**
 * pplte_env_list - populate env linked list
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int ppulte_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; nfo->env[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}

