#include "shell.h"

/**
 * is_cmd_f - determines executable command
 * @info: info struct
 * @path: src
 * Return: 1, 0 otherwise
 */
int is_cmd_f(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_charc - copies characters
 * @pathstr: PATH
 * @start: first index
 * @stop: last index
 *
 * Return: pointer
 */
char *dup_charc(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, b = 0;

	for (b = 0, i = start; i < stop; i++)
		if (pathstr[i] != ':')
			buf[b++] = pathstr[i];
	buf[b] = 0;
	return (buf);
}

/**
 * find_path - locates cmd
 * @info: info struct
 * @pathstr: PATH string
 * @cmd: src
 * Return: path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, curr_pos = 0;
	char *path;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd_f(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			path = dup_charc(pathstr, curr_pos, i);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd_f(info, path))
				return (path);
			if (!pathstr[i])
				break;
			curr_pos = i;
		}
		i++;
	}
	return (NULL);
}

