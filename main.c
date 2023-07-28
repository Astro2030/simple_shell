#include "shell.h"

/**
 * main - entry point of our shell
 * Return: Nothing
 */

int main(void)
{
	char *str;
	char **tokens;
	int status;
	char prompt[] = "$ ";

	do {
		write(1, prompt, sizeof(prompt) - 1);
		str = read_input();

		if (str[0] == '\0')
		{
			free(str);
			continue;
		}

		tokens = tokenize_input(str);
		status = token_execution(tokens);

		free_tokens(tokens);

	} while (status != 0);

	return (0);
}
