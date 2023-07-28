#include "shell.h"

/**
 * check_absolute_path - checks if string contains abs path
 * @command: string to be checked
 * Return: NULL
 */

char *check_absolute_path(char *command)
{
	if (command[0] == '/')
	{
		if (access(command, X_OK) == 0)
		{
			return (command);
		}
	}

	return (NULL);
}


/**
 * check_in_each_path - Checks each directory in the PATH environment variable
 * @command: command to be checked
 * Return: full path
 */
char *check_in_each_path(char *command)
{
	char *path_env = getenv("PATH");
	char *path_start = path_env;
	char *path_end;
	size_t command_len = strlen(command);
	size_t executable_path_size;
	char *executable_path;

	while (*path_start != '\0')
	{
		path_end = strchr(path_start, ':');
		if (path_end == NULL)
		{
			path_end = path_start + strlen(path_start);
		}
		executable_path_size = (path_end - path_start) + 1 + command_len + 1;
		executable_path = malloc(executable_path_size);
		if (executable_path == NULL)
		{
			perror("allocation error");
			exit(EXIT_FAILURE);
		}
		strncpy(executable_path, path_start, path_end - path_start);
		executable_path[path_end - path_start] = '\0';
		strcat(executable_path, "/");
		strcat(executable_path, command);
		if (access(executable_path, X_OK) == 0)
		{
			return (executable_path);
		}
		free(executable_path);
		path_start = path_end;
		if (*path_start == ':')
		{
			path_start++;
		}
	}

	return (NULL);
}

/**
 * search_command_in_path - search command in path and directory
 * @command: string to be searched
 * Return: full_path
 */

char *search_command_in_path(char *command)
{
	char *full_path = check_absolute_path(command);

	if (full_path == NULL)
	{
		full_path = check_in_each_path(command);
	}

	return (full_path);

}

/**
 * find_full_path - combines all path functions
 * @command: string to be executed
 * Return: full_path
 */

char *find_full_path(char *command)
{
	char *full_path = search_command_in_path(command);

	return (full_path);
}

/**
 * handle_env - handles environment variable
 * @tokens: string entered
 * Return: 1 on succes
 */

int handle_env(char **tokens)
{
	char **env;
	char *current_env;

	for (env = environ; *env != NULL; env++)
	{
		current_env = *env;
		while (*current_env)
		{
			_putchar(*current_env);
			current_env++;
		}
		_putchar('\n');
	}

	free_tokens(tokens);
	return (1);
}
