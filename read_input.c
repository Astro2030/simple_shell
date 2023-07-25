#include "shell.h"

/**
 * read_input - gets input from stdin stream
 * Return: pointer to the string input.
 */

char *read_input(void)
{
	char *input_string = NULL;

	input_string = custom_getline();

	if (input_string == NULL)
	{
		perror("readline");
		exit(EXIT_FAILURE);
	}

	return (input_string);
}

/**
 * tokenize_input - splitting input_string into a list of args
 * @input_string: line to be tokenized
 * Return: NULL terminated array of string pointers
 */

char **tokenize_input(char *input_string)
{
	int buffersize = TOKEN_BUFFSIZE;
	int index = 0;
	char **tokens = malloc(sizeof(char *) * buffersize);
	char *token;
	char *saveptr = NULL;

	if (tokens == NULL)
	{
		fprintf(stderr, "allocation error\n");
		exit(EXIT_FAILURE);
	}

	token = strtok_custom(input_string, TOKEN_DELIMETER, &saveptr);
	while (token != NULL)
	{
		tokens[index] = strdup(token);
		index++;


		if (index >= buffersize)
		{
			buffersize += TOKEN_BUFFSIZE;
			tokens = realloc(tokens, buffersize * sizeof(char *));
			if (!tokens)
			{
				fprintf(stderr, "allocation error\n");
				exit(EXIT_FAILURE);
			}
		}
		token = strtok_custom(NULL, TOKEN_DELIMETER, &saveptr);
	}
	tokens[index] = NULL;

	return (tokens);
}

/**
 * token_execution - executes commands
 * @tokens: commands to be executed
 * Return: 1 on success
 */

int token_execution(char **tokens)
{
	pid_t pid;
	int status;
	char *full_path;

	full_path = find_full_path(tokens[0]);
	if (full_path == NULL)
	{
		if (strcmp(tokens[0], "exit") == 0)
		{
			return (handle_exit(tokens));
		}
		else if (strcmp(tokens[0], "env"))
		{
			return (handle_env(tokens));
		}
		fprintf(stderr, "Command not found: %s\n", tokens[0]);
		return (1);
	}

	pid = fork();
	if (pid == 0)
	{
		if (execve(full_path, tokens, environ) == -1)
		{
			perror("execve");
		}
		exit(EXIT_FAILURE);
	}
	else if (pid < 0)
	{
		perror("lsh");
	}
	else
	{
		do {
			waitpid(pid, &status, WUNTRACED);
		} while (!WIFEXITED(status) && !WIFSIGNALED(status));
	}

	return (1);
}
