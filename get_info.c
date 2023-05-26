#include "shell.h"

/**
 * clr_info - initializes info_t struct
 * @info: struct address
 */
void clr_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}

/**
 * setinfo - initializes info_t struct
 * @info: struct address
 * @av: argument vector
 */
void setinfo(info_t *info, char **av)
{
	int i = 0;

	info->fname = av[0];
	if (info->arg)
	{
		info->argv = strtow(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _stridup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (i = 0; info->argv && info->argv[i]; i++)
			;
		info->argc = i;

		replace_aliass(info);
		replaces_vars(info);
	}
}

/**
 * free_infot - frees info_t struct fields
 * @info: struct address
 * @all: true if freeing all fields
 */
void free_infot(info_t *info, int all)
{
	free(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (all)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			freeall_list(&(info->env));
		if (info->history)
			freeall_list(&(info->history));
		if (info->alias)
			freeall_list(&(info->alias));
		free(info->environ);
			info->environ = NULL;
		b_free((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		eputchar(BUF_FLUSH);
	}
}
