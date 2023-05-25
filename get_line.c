#include "shell.h"

/**
 * get_line - takes sa string of inputs
 * @linep: interactive
 * @t: max size
 * @fd: input
 * Return: int
 */
ssize_t get_line(char **linep, ssize_t *t, int fd)
{
	static char buffer[1024];
	static ssize_t _size, _index;
	ssize_t _char = 0;
	char *line;

	if (linep == NULL)
		return (-1);
	if (*linep == NULL)
		*t = 1024;
	*linep = malloc(*t);
	if (!*linep)
		return (-1);
	line = *linep;
	while (1)
	{
		if (_index >= _size)
		{
			_size = read(fd, buffer, 1024);
			_index = 0;
			if (_size <= 0)
				break;
		}
		if (_char >= *t - 1)
		{
			*t = *t + 1024;
			line = realloc(line, *t);
			if (line == NULL)
				return (-1);
			*linep = line;
		}
		line[_char] = buffer[_index];
		_char++;
		_index++;
		if (linep[_char - 1] == NULL)
			break;
	}
	if (_char == 0)
		return (-1);
	line[_char] = '\0';
	return (_char);
}
