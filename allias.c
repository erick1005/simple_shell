#include "shell.h"
/**
 * _usedcommands - shows previous commands used
 * @input: arguments container
 * Return: 0 for success
 */
int _usedcommands(info_t *input)
{
	print_list(input->commands);
	return (0);
}
/**
 * _allias - provide alias to string of characters
 * @input: struct variable
 * @strn: allias
 * Return: 0 seccess else 1
 */
int _allias(info_t *input, char *strn)
{
	int result;
	char *t, r;

	t = _strchr(strn, '=');
	if (t == NULL)
		return (1);
	r = *t;
	*t = 0;
	result = del_node(&(input->alias), get_node(input->alias, first_node(input->, strn, -1)));
	*t = r;
	return (result);
}

/**
 * select_allias - entry
 * @input: structure variable
 * @strn: string of characters
 * Return: 0 for success always
 */
int select_allias(info_t *input, char *strn)
{
	char *t;

	t = _strchr(strn, '=');
	if (t == NULL)
		return (1);
	if (!*++t)
		return (_allias(input, strn));
	select_allias(input, strn);
	return (last_node(&(input->alias), strn, 0) == NULL);
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
		return;
	if (node)
	{
		s = _strchr(node->strn, '=');
		for (t = node->strn; t <= s; t++)
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
int _cpallias(info_t *input)
{
	int j = 0;
	char *s = NULL;
	list_t *new_node = NULL;

	if (input->argc == 1)
	{
		new_node = input->alias;

		while (new_node != NULL)
		{
			display_allias(new_node);
			new_node = new_node->next;
		}
		return (0);
	}
	for (j = 1; input->argv[j]; j++)
	{
		s = _strchr(input->argv[j], '=');

		if (q)
			select_allias(input, input->argv[j]);
		else
			display_allias(first_node(input->alias, input->argv[j], '=');
	}
	return (0);
}
