#ifndef SHELL_H
#define SHELL_H

/*  Libraries   */
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <sys/wait.h>
#include <unistd.h>
#include <string.h>
#include <errno.h>

/* reading line */
#define TOKEN_DELIMETER " \t\r\n\a"
#define TOKEN_BUFFSIZE 64
#define READ_BUFFER_SIZE 1024

extern char **environ;

/*---prototypes---*/
int _putchar(char c);
char *find_full_path(char *command);
char *read_input(void);
char **tokenize_input(char *str);
int token_execution(char **tokens);
void free_tokens(char **tokens);
char *check_absolute_path(char *command);
char *check_in_each_path(char *command);
char *search_command_in_path(char *command);
int handle_exit(char **tokens);
int handle_env(char **tokens);
void exit_shell(void);
char *custom_getline(void);
char *strtok_custom(char *str, const char *delim, char **saveptr);
int read_line(char *buffer, int *buffer_index, int *buffer_length);

#endif
