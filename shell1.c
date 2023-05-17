#include "shell.h"

/**
 * inter - returns true if in interactive mode
 * @struc: structure address
 *
 * Return: 1 in interactive mode 0 otherwise
 *
 */

int inter(info_t *struc)
{
	return (isatty(STDIN_FILENO) && struc->readfd <= 2);
}
/**
 * checker - checks if character is delimeter
 * @e: char to check
 * @check: delimeter string
 * Return: 1 if true, otherwise 0
 */
int checker(char e, char *check)
{
	while (*check)
		if (*check++ == e)
			return (1);
	return (0);
}
/**
 * alpha - checks for alphabetic character
 * @e: character input
 * Return: 1 if e is alphabetic otherwise 0
 */

int alpha(int e)
{
	if ((e >= 'a' && e <= 'z') || (e >= 'A' && e <= 'Z'))
		return (1);
	else
		return (0);
}
/**
 * conver - converts string to integer
 * @s: string to convert
 * Return: 0 if string only otherwise 1
 */
int conver(char *s)
{
	int m, sign = 1, flag = 0, output;
	unsigned int result = 0;

	for (m = 0; s[m] != '\0' && flag != 2; m++)
	{
		if (s[m] == '-')
			sign *= -1;

		if (s[m] >= '0' && s[m] <= '9')
		{
			flag = 1;
			result *= 10;
			result += (s[m] - '0');
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
