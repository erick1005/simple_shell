#include "shell.h"

/**
 * input_buff - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *info, char **buf, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _get_line(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buf;
			}
		}
	}
	return (r);
}

/**
 * gett_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t gett_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, n, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *m;

	_putchar(BUF_FLUSH);
	r = input_buff(info, &buf, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		n = i; /* init new iterator to current buf position */
		m = buf + i; /* get pointer for return */

		check_chain(info, buf, &n, i, len);
		while (n < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &n))
				break;
			n++;
		}

		i = n + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = m; /* pass back pointer to current command position */
		return (_strlen(m)); /* return length of current command */
	}

	*buf_p = buf; /* else not a chain, pass back buffer from _get_line() */
	return (r); /* return length of buffer from _get_line() */
}

/**
 * read_buff - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buff(info_t *info, char *buf, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buf, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * _get_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: o
 */
int _get_line(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t i, len;
	size_t b;
	ssize_t r = 0, o = 0;
	char *m = NULL, *new_p = NULL, *c;

	m = *ptr;
	if (m && length)
		o = *length;
	if (i == len)
		i = len = 0;

	r = read_buff(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buf + i, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(m, o, o ? o + b : b + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (m ? free(m), -1 : -1);

	if (o)
		_strncat(new_p, buf + i, b - i);
	else
		_strncpy(new_p, buf + i, b - i + 1);

	o += b - i;
	i = b;
	m = new_p;

	if (length)
		*length = o;
	*ptr = m;
	return (o);
}

/**
 * sigint_Handler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
