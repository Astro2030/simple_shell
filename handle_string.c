#include "shell.h"


/**
 * _putchar - writes single character to the stdoutput
 * @c: the character to print
 * Return: 1 on success
 * On error, -1 is returned
 */

int _putchar(char c)
{
	return (write(1, &c, 1));
}

/**
 * custom_getline - custom getline function
 * Description:function reads characters from standard input into
 * a buffer and returns a line as a dynamically allocated string.
 * Return: On success, returns a pointer to the line, on failure
 */
char *custom_getline(void)
{
	static char buffer[READ_BUFFER_SIZE];
	static int buffer_index, buffer_length, eof_flag;
	char *line = (char *)malloc(READ_BUFFER_SIZE), *new_line, ch;
	int line_length = 0;

	if (line == NULL)
	{
		perror("allocation error");
		exit(EXIT_FAILURE);
	}
	while (1)
	{
		if (read_line(buffer, &buffer_index, &buffer_length))
		{
			eof_flag = 1;
			break;
		}
		ch = buffer[buffer_index++];
		if (ch == '\n' || ch == '\0')
			break;
		line[line_length++] = ch;
		if (line_length >= READ_BUFFER_SIZE)
		{
			new_line = (char *)realloc(line, line_length + 1);
			if (new_line == NULL)
			{
				perror("Memory allocation error");	
				exit(EXIT_FAILURE);
			}
			line = new_line;
		}
	}
	line[line_length] = '\0';
	if (eof_flag && line_length == 0)
	{
		_putchar('\n');
		exit(EXIT_SUCCESS);
	}
	return (line);
}

/**
 * read_line - reads a line from stdin
 * @buffer: where line read is stored
 * @buffer_index: current position of the buffer
 * @buffer_length: size of the buffer
 * Return: 0 on success
 */
int read_line(char *buffer, int *buffer_index, int *buffer_length)
{
	if (*buffer_index == *buffer_length)
	{
	*buffer_length = read(STDIN_FILENO, buffer, READ_BUFFER_SIZE);
	if (*buffer_length == 0)
		return (1);
	*buffer_index = 0;
	}
	return (0);
}


/**
 * strtok_custom - custom version of strtok function
 * @str: string to be tokenized
 * @delim: delimeters used for tokenization
 * @saveptr: pointer to keep track of the current position in the string
 * Return: pointer to the next token in string or NULL if no more tokens
 */

char *strtok_custom(char *str, const char *delim, char **saveptr)
{
	char *token;

	if (str == NULL)
	{
		str = *saveptr;
	}

	str += strspn(str, delim);
	if (*str == '\0')
	{
		return (NULL);
	}

	token = str;
	str = strpbrk(token, delim);
	if (str == NULL)
	{
		*saveptr = token + strlen(token);
	}
	else
	{
		*str = '\0';
		*saveptr = str + 1;
	}

	return (token);
}
