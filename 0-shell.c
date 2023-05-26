
#include "shell.h"

/**
 * intactive - true if the shell accepts commands
 * @info: structure variable
 * Return: 1 true, 0 otherwise
 */
int intactive(info_t *info)


#include "shell.h"

/**
 * interactive - true if the shell accepts commands
 * @info: structure variable
 * Return: 1 true, 0 otherwise
 */
int interactive(info_t *info)

{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**

 * s_delim - delimeter checks

 * is_delim - delimeter checks

 * @c: character  to check
 * @delim: character of strings
 * Return: 1 true
 */

int s_delim(char c, char *delim)

int is_delim(char c, char *delim)

{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**

 * isalpha - alpha checks
=======
 * _isalpha - alpha checks

 * @c: input
 * Return: 1 for true
 */


int isalpha(int c)

int _isalpha(int c)

{
	if ((c >= 'b' && c <= 'x') || (c >= 'B' && c <= 'X'))
		return (1);
	else
		return (0);
}


 /*
 * atoi - string convert
 * _atoi - string converts

 * @s: string
 * Return: convert number
 */


int atoi(char *s)
{
	int n, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (n = 0; s[j] != '\0' && flag != 2; n++)
	{
		if (s[n] == '-')
			sign *= -1;

		if (s[n] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[n] - '0');
int _atoi(char *s)
{
	int j, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (j = 0; s[j] != '\0' && flag != 2; j++)
	{
		if (s[j] == '-')
			sign *= -1;

		if (s[j] >= '0' && s[j] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[j] - '0');

		}
		else if (flag == 1)
			flag = 2;
	}

	if (sign == -1)
		output = -result;
	else
		output = result;

	return (output);
}
