#include "shell.h"

/**
 * _exitstatus - closes shell with status
 * @info: argument structure
 * Return: status
 */
int _exitstatus(info_t *info)
{
	int check;

	if (*(info->argv + 1))
	{
		check = erratoi(*(info->argv + 1));
		if (check == -1)
		{
			info->status = 2;
			print_errr(info, "unacceted input:");
			_eputs(*(info->argv + 1));
			_eputchar('\n');
			return (1);
		}
		info->err_num = erratoi(*(info->argv + 1));
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * _directory -directory change
 * @info: arguments
 * Return: 0 for success
 */
int _directory(info_t *info)
{
	char *c, *d, buffer[1024];
	int ch;

	c = getcwd(buffer, 1024);
	if (c == NULL)
		_eputs("TODO:>>getcwd failure msg<<\n");
	if (!*(info->argv + 1))
	{
		d = getenvi(info, "HOME=");
		if (d == NULL)
			ch = chdir((d = getenvi(info, "PWD=")) ? d : "/");
		else
			ch = chdir(d);
	}
	else if (strcmp(*(info->argv + 1), "-") == 0)
	{
		if (!getenvi(info, "OLDPWD="))
		{
			_eputs(c);
			_putchar('\n');
			return (1);
		}
		_eputs(getenvi(info, "OLDPWD=")), _putchar('\n');
		ch = chdir((d = getenvi(info, "OLDPWD=")) ? d : "/");
	}
	else
		ch = chdir(*(info->argv + 1));
	if (ch == -1)
	{
		print_errr(info, "cant change directory to");
		_eputs(*(info->argv + 1)), _eputchar('\n');
	}
	else
	{
		ssetenv(info, "OLDPWD", getenvi(info, "PWD="));
		ssetenv(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}
/**
 * help - entry
 * @info: variable argumnets
 * Return: 0 for successs
 */
int help(info_t *info)
{
	char **arg;

	arg = info->argv;
	_eputs("use help when the function isnt available");
	if (0)
		_eputs(*arg);
	return (0);
}
