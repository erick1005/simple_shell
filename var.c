#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: parameter struct
 * @buf: char buffer
 * @y: address of current position
 *
 * Return: 1, 0 otherwise
 */
int is_chain(info_t *info, char *buf, size_t *y)
{
	size_t n = *y;

	if (buf[n] == '|' && buf[n + 1] == '|')
	{
		buf[n] = 0;
		n++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[n] == '&' && buf[n + 1] == '&')
	{
		buf[n] = 0;
		n++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[n] == ';') /* found end of this command */
	{
		buf[n] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*y = n;
	return (1);
}

/**
 * checks_chain - checks chaining status
 * @info: parameter struct
 * @buf: char buffer
 * @y: address of current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void checks_chain(info_t *info, char *buf, size_t *y, size_t i, size_t len)
{
	size_t n = *y;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			n = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			n = len;
		}
	}

	*y = n;
}

/**
 * replace_aliass - replaces aliases
 * @info: the parameter struct
 *
 * Return: 1, 0 otherwise
 */
int replace_aliass(info_t *info)
{
	int i;
	list_t *node;
	char *y;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		y = _strchr(node->str, '=');
		if (!y)
			return (0);
		y = _strdup(y + 1);
		if (!y)
			return (0);
		info->argv[0] = y;
	}
	return (1);
}

/**
 * replaces_vars - replaces vars
 * @info: the parameter struct
 * Return: 1, 0 otherwise
 */
int replaces_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replaces_string(&(info->argv[i]),
					_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replaces_string(&(info->argv[i]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replaces_string(&(info->argv[i]),
					_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replaces_string(&info->argv[i], _strdup(""));

	}
	return (0);
}

/**
 * replaces_string - replaces string
 * @old: old string
 * @new: new string
 * Return: 1, 0 otherwise
 */
int replaces_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}

