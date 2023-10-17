#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string.h>
#include <limits.h>
#include <signal.h>
#include <ctype.h>

#define FALSE 0
#define TRUE 1
#define NEITHER 2
#define MATCH 3
#define PREFIX 4
#define EXIT_SHELL 5
#define SKIP_FORK 6
#define DO_EXECVE 7

/**
 * struct Alias - singly linked list
 * @name: name of alias
 * @value: command that alias calls
 * @next: points to next node
 */
typedef struct Alias
{
	char *alias_name;
	char *alias_value;
	struct Alias *next_alias;
} Alias;

extern char **environ;

extern int status;

extern int line_num;

extern char *shell_name;

char *my_get_array_element(char **array, const char *element_prefix);

int handle_commands(char **args);

int built_ins(char **args);

int and_or(char **args, char operator, int last_compare);

char *find_executable_path(char **args);

int execute_command(char **args);

char *sanitize_input(char *input_buffer, size_t *input_size);

int has_unexpected_chars(const char *input);

void print_error_message(const char *command, const char *argument);

void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size);

int _getline(char **line_ptr, size_t *n, int file);

char *evaluate_variables(const char *argument);

size_t custom_strlen(const char *str);
