#include "shell.h"

void sigint_Handler(int sig);
char *_strchr(char *s, int c);
char *_realloc(void *ptr, size_t old_size, size_t new_size);
char *_strncat(char *dest, const char *src, size_t n);
char *_strncpy(char *dest, const char *src, size_t n);
void _puts(char *str);
int get_input_line(info_t *info, char **ptr, size_t *length);
void build_history_list(info_t *info, char *buffer, int histcount);
int input_buf(info_t *info, char **ptr, size_t *length);
void check_chain(info_t *info, char *buffer, int *j, int i, size_t len);
int is_chain(info_t *info, char *buffer, int *j);

/**
 * input_buff - buffers chained commands
 * @info: parameter struct
 * @buffer: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buff(info_t *info, char **buffer, size_t *len)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, sigint_Handler);
#if USE_GETLINE
		r = get_input_line(buffer, &len_p, stdin);
#else
		r = get_input_line(info, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0'; /* remove trailing newline */
				r--;
			}
			info->linecount_flag = 1;
			remove_comments(*buffer);
			build_history_list(info, *buffer, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = r;
				info->cmd_buf = buffer;
			}
		}
	}
	return (r);
}

/**
 * getinput - gets  line minus  newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t getinput(info_t *info)
{
	static char *buffer; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t r = 0;
	char **buf_p = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	r = input_buf(info, &buffer, &len);
	if (r == -1) /* EOF */
		return (-1);
	if (len) /* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		p = buffer + i; /* get pointer for return */

		check_chain(info, buffer, &j, i, len);
		while (j < len) /* iterate to semicolon or end */
		{
			if (is_chain(info, buffer, &j))
				break;
			j++;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			i = len = 0; /* reset position and length */
			info->cmd_buf_type = CMD_NORM;
		}

		*buf_p = p; /* pass back pointer to current command position */
		return (strlen(p)); /* return length of current command */
	}

	*buf_p = buffer; /* else not a chain, pass back buffer from _getline() */
	return (r); /* return length of buffer from _getline() */
}

/**
 * read_buffer - reads a buffer
 * @info: parameter struct
 * @buffer: buffer
 * @i: size
 *
 * Return: r
 */
ssize_t read_buffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t r = 0;

	if (*i)
		return (0);
	r = read(info->readfd, buffer, READ_BUF_SIZE);
	if (r >= 0)
		*i = r;
	return (r);
}

/**
 * get_input_line - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int get_input_line(info_t *info, char **ptr, size_t *length)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, len;
	size_t k;
	ssize_t r = 0, s = 0;
	char *p = NULL, *new_p = NULL, *c;

	p = *ptr;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;

	r = get_input_line(info, buffer, &len_p);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	c = _strchr(buffer + i, '\n');
	k = c ? 1 + (unsigned int)(c - buffer) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p) /* MALLOC FAILURE! */
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buffer + i, k - i);
	else
		_strncpy(new_p, buffer + i, k - i + 1);

	s += k - i;
	i = k;
	p = new_p;

	if (length)
		*length = s;
	*ptr = p;
	return (s);
}

/**
 * sigint_Handler - blocks ctrl-C
 * @sig_number: the signal number
 *
 * Return: void
 */
void sigint_Handler(__attribute__((unused))int sig_number)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}

