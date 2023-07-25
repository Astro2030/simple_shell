#include "shell.h"

/**
 * free_tokens - frees memory used by tokens array
 * @tokens: array of tokens
 */

void free_tokens(char **tokens)
{
	int i;

	if (tokens == NULL)
	{
		return;
	}

	for (i = 0; tokens[i] != NULL; i++)
	{
		free(tokens[i]);
	}
	free(tokens);
}

/**
 * handle_exit - Exits the shell program.
 * @tokens: command to exit
 * Return: 0 on success
 */
int handle_exit(char **tokens)
{
	int exit_status = 0;

	if (tokens[1] != NULL)
	{
		exit_status = atoi(tokens[1]);
	}

	free_tokens(tokens);
	exit(exit_status);
	return (0);
}
