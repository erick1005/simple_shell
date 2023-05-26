#include "shell.h"

/**
 * err_atoi - converts a string to an integer
 * @o: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int  err_atoi(char *o)
{
	int i = 0;
	unsigned long int result = 0;

	if (*o == '+')
		o++;  /* TODO: why does this make main return 255? */
	for (i = 0;  o[i] != '\0'; i++)
	{
		if (o[i] >= '0' && o[i] <= '9')
		{
			result *= 10;
			result += (o[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}

/**
 * printerror - prints an error message
 * @info: the parameter & return info struct
 * @estr: string containing specified error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void printerror(info_t *info, char *estr)
{
	_eputsd(info->fname);
	_eputsd(": ");
	fprint_d(info->line_count, STDERR_FILENO);
	_eputsd(": ");
	_eputsd(info->argv[0]);
	_eputsd(": ");
	_eputsd(estr);
}

/**
 * fprint_d - function prints a decimal (integer) number (base 10)
 * @input: the input
 * @fd: the filedescriptor to write to
 *
 * Return: number of characters printed
 */
int fprint_d(int input, int fd)
{
	int (*__putchar)(char) = __putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (fd == STDERR_FILENO)
		__putchar = eputchar;
	if (input < 0)
	{
		_abs_ = -input;
		__putchar('-');
		count++;
	}
	else
		_abs_ = input;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * convert_numb - converter function, a clone of itoa
 * @num: number
 * @base: base
 * @flags: argument flags
 *
 * Return: string
 */
char *convert_numb(long int num, int base, int flags)
{
	static char *array;
	static char buffer[50];
	char sign = 0;
	char *ptr;
	unsigned long o = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		o = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	ptr = &buffer[49];
	*ptr = '\0';

	do	{
		*--ptr = array[o % base];
		o /= base;
	} while (o != 0);

	if (sign)
		*--ptr = sign;
	return (ptr);
}

/**
 * remove_com - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_com(char *buf)
{
	int i;

	for (i = 0; buf[i] != '\0'; i++)
		if (buf[i] == '#' && (!i || buf[i - 1] == ' '))
		{
			buf[i] = '\0';
			break;
		}
}
