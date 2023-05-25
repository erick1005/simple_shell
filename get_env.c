#include "shell.h"

/**
 * ggetenv - returns the environment
 * @info:variable argument
 * Return: 0 for success
 */
char ggetenv(info_t *info)
{
	if (info->environ == NULL)
	{
		info->environ = last_node(info->env, var);
	}
	return (info->env_changed);
}
/**
 * uunsetenv - deletes environment
 * @info: env variable
 * Return: 1 on success
 */
int uunsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t s = 0;
	char *c;

	if (node == NULL || var == NULL)
		return (0);
	while (node)
	{
		c = starts_with(node->str, var);
		if (c && *c == '=')
		{
			info->env_changed = delete_node(&(info->env), s);
			s = 0;
			node = info->env;
		}
		node = node->next;
		s++;
	}
	return (info->env_changed);
}
/**
 * ssetenv - creates a new environment
 * @info: input
 * @var: variable inputs
 * @value: char of strings
 * Return: 0 for success
 */
int ssetenv(info_t *info, char *var, char *value)
{
	char *buff = NULL;
	list_t *new_node;
	char *s;

	if (var == NULL || value == NULL)
	{
		return (0);
	}
	buff = malloc(strlen(var) + strlen(value) + 2);
	if (buff == NULL)
		return (1);
	strcpy(buff, var);
	strcat(buff, "=");
	strcat(buff, value);
	new_node = info->env;

	while (new_node)
	{
		s = starts_with(new_node->str, var);
		if (s && s == '=')
		{
			free(new_node->str);
			new_node->str = buff;
			info->env_changed = 1;
			return (0);
		}
		new_node = new_node->next;
	}
	last_node(&(info->env), buff, 0);
	free(buff);
	info->env_changed = 1;
	return (0);
}
