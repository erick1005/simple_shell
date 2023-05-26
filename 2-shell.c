#include "shell.h"
/**
 * myexit - stops shell
 * @info: struct variables
 * Return: status return exit
 */
int myexit(info_t *info)
{
	int exitcheck;

	if (info->argv[1])
	{
		exitcheck = erra_toi(info->argv[1]);
		if (exitcheck == -1)
		{
			info->status = 2;
			printerror(info, "Illegal number: ");
			_eputsd(info->argv[1]);
			eputchar('\n');
			return (1);
		}
		info->err_num = erra_toi(info->argv[1]);
		return (-2);
	}
	info->err_num = -1;
	return (-2);
}

/**
 * mycd - directory change
 * @info: struct variable
 * Return: Always 0
 */
int mycd(info_t *info)
{
	char *o, *dir, buffer[1024];
	int chdir_ret;

	o = getcwd(buffer, 1024);
	if (!o)
		_eputsd("TODO: >>getcwd failure emsg here<<\n");
	if (!info->argv[1])
	{
		dir = getenva(info, "HOME=");
		if (!dir)
			chdir_ret = /* TODO: what should this be? */
				chdir((dir = getenva(info, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (strcmp(info->argv[1], "-") == 0)
	{
		if (!getenva(info, "OLDPWD="))
		{
			_eputsd(o);
			eputchar('\n');
			return (1);
		}
		_eputsd(getenva(info, "OLDPWD=")), eputchar('\n');
		chdir_ret = /* TODO: what should this be? */
			chdir((dir = getenva(info, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);
	if (chdir_ret == -1)
	{
		printerror(info, "can't cd to ");
		_eputsd(info->argv[1]), eputchar('\n');
	}
	else
	{
		_setenvmd(info, "OLDPWD", getenva(info, "PWD="));
		_setenvmd(info, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * _mychelp - current directory change
 * @info: arguments Structure
 * Return: 0 success
 */
int _mychelp(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_eputsd("help call works. Function not yet implemented \n");
	if (0)
		_eputsd(*arg_array);
	return (0);
}
