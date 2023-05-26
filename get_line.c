#include "shell.h"

/**
 * _realloc - reallocate memory
 * @ptr: pointer
 * @old_size: byte size
 * @new_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */

void *_real_loc(void *ptr, unsigned int old_size, unsigned int new_size);

void *_real_loc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *p;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	p = malloc(new_size);
	if (!p)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		p[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (p);
}

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

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		r = _getline(buf, &len_p, stdin);
#else
		r = _getline(info, buf, &len_p);
#endif
		if (r > 0)
		{
			if ((*buf)[r - 1] == '\n')
			{
				(*buf)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_com(*buf);
			build_histlist(info, *buf, info->histcount++);

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
	static char *buf;
	static size_t i, n, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *m;

	eputchar(BUF_FLUSH);
	r = input_buff(info, &buf, &len);
	if (r == -1)
		return (-1);
	if (len)
	{
		n = i;
		m = buf + i;
		checks_chain(info, buf, &n, i, len);
		while (n < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &n))
				break;
			n++;
		}
		i = n + 1;
		if (i >= len)
		{
			i = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}
		*buf_p = m;
		return (_strlen(m));
	}
	*buf_p = buf;
	return (r);
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
	c = strchr(buf + i, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _real_loc(m, o, o ? o + b : b + 1);
	if (!new_p)
		return (m ? free(m), -1 : -1);

	if (o)
		strncat(new_p, buf + i, b - i);
	else
		strncpy(new_p, buf + i, b - i + 1);
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
	puts("\n");
	puts("$ ");
	eputchar(BUF_FLUSH);
}
