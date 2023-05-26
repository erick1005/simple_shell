#include "shell.h"

/**
 * _myenv - current environmt
 * @info: variable struct.
 * Return: 0 for success
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - environmt variable
 * @info: argument struct.
 * @name:input
 * Return: pointer
 */
char *_getenv(info_t *info, const char *name)
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
 * _mysetenv -  customized variable
 * @info: struct arguments.
 *  Return: Always 0 success
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - deletes variable
 * @info: argument struct.
 * Return: success 0
 */
int _myunsetenv(info_t *info)
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
 * populate_env_list - entry
 * @info: argument structure
 * Return: 0 for success
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	while (i != '\0')
	{
		add_node_end(&node, 0, 0);
		i++;
	}
	info->env = node;
	return (0);
}

