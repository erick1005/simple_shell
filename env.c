#include "shell.h"

/**
 * envi - prints current environment
 * @en: contain arguements
 * Return: always 0
 */

int envi(info_t *en)
{
	print_list_Str(en->env);
	return (0);
}
/**
 * getenv - gets value of enviroment variable
 * @en: contains arguements
 * @nm: variable name
 *
 * Return: the value
 */
char *getenv(info_t *en, const char *nm)
{
	list_t *node = en->env;
	char *n;

	while (node)
	{
		n = starts_with(node->str, nm);
		if(n && *n)
			return (n);
		node = node->next;
	}
	return (NULL);
}

/**
 *setenv - create new environment
 *@en: contains arguements
 *Return: Always 0
 */
int setenv(info_t *en)
{
	if (en->argc != 3)
	{
		eputs("Incorrect numberof arguements\n");
		return (1);
	}
	if (setenv(en, en->argv[1], en->argv[2]))
		return (0);
	return (1);
}
/**
 * rmenv - remove environment variable
 * @en: contains arguements
 * Return: Always 0
 */

int rmenv(info_t *en)
{
	int i;
	if (en->argc == 1)
	{
		eputs("Too few arguements.\n");
		return (1);
	}
	for(i = 1; i <= en->argc; i++)
		rmenv(en, en->argv[i]);
	return (0);
}
/**
 * pen - populate enviroment listt
 * @en: contains arguements
 * Return: Always 0
 */
int penv(info_t *en)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&node, environ[i], 0);
	info->env = node;
	return (0);
}
