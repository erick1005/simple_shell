#include "shell.h"
/**
 * _usedcommands - shows previous commands used
 * @input: arguments container
 * Return: 0 for success
 */
int _usedcommands(info_t *info)
{
	print_d(info->history);
	return (0);
}
/**
 * _allias - provide alias to string of characters
 * @input: struct variable
 * @strn: allias
 * Return: 0 seccess else 1
 */
int _allias(info_t *info, char *strn)
{
	int result;
	char *t, r;

	t = strchr(strn, '=');
	if (t == NULL)
		return (1);
	r = *t;
	*t = 0;
	result = delete_node(&(info->alias),
			last_node(info->alias, first_node(info->alias, strn, -1)));
	*t = r;
	return (result);
}

/**
 * select_allias - entry
 * @input: structure variable
 * @strn: string of characters
 * Return: 0 for success always
 */
int select_allias(info_t *info, char *strn)
{
	char *t;

	t = strchr(strn, '=');
	if (t == NULL)
		return (1);
	if (!*++t)
		return (_allias(info, strn));
	select_allias(info, strn);
	return (last_node(&(info->alias), strn, 0) == NULL);
}
/**
 * display_allias - output name;
 * @node: src node
 * Return: 0 for success
 */
int display_allias(list_t *node)
{
	char *s = NULL;
	char *t = NULL;

	if (node == NULL)
		return (-1);
	if (node)
	{
		s = strchr(node->str, '=');
		for (t = node->str; t <= s; t++)
		{
			_putchar(*t);
			_putchar('\n');
			_putchar(s + 1);
			_putchar('\n');
		}
		return (0);
	}
	return (1);
}
/**
* _cpallias - copies default allias
* @input: structure argument
* Return: 0 for success
*/
int _cpallias(info_t *info)
{
	int j = 0;
	char *s = NULL;
	list_t *new_node = NULL;

	if (info->argc == 1)
	{
		new_node = info->alias;

		while (new_node != NULL)
		{
			display_allias(new_node);
			new_node = new_node->next;
		}
		return (0);
	}
	for (j = 1; info->argv[j]; j++)
	{
		s = strchr(info->argv[j], '=');

		if (s)
		{
			select_allias(info, info->argv[j]);
		}
		else
		{
			display_allias(first_node(info->alias, info->argv[j], '='));
		}
	}
	return (0);
}
