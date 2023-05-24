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
			print_error(info, "unacceted input:");
			error_puts(*(info->argv + 1));
			error_char('\n');
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
		_puts("TODO:>>getcwd failure msg<<\n");
	if (!*(info->argv + 1))
	{
		d = getenvi(info, "HOME=");
		if (d == NULL)
			ch = chdir((d = getenvi(info, "PWD=")) ? d : "/");
		else
			ch = chdir(d);
	}
	else if (_strcmp(*(info->argv + 1), "-") == 0)
	{
		if (!getenvi(info, "OLDPWD="))
		{
			_puts(c);
			_putchar('\n');
			return (1);
		}
		_puts(getenvi(info, "OLDPWD=")), _putchar('\n');
		ch = chdir((d = getenvi(info, "OLDPWD=")) ? d : "/");
	}
	else
		ch = chdir(*(info->argv + 1));
	if (ch == -1)
	{
		print_errr(info, "cant change directory to");
		error_puts(*(info->argv + 1), error_char('\n');
	}
	else
	{
		mysetenvi(info, "OLDPWD", getenvi(info, "PWD="));
		mysetenvi(info, "PWD", getcwd(buffer, 1024));
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
	_puts("use help when the function isnt available");
	if (0)
		_puts(*arg);
	return (0);
}
