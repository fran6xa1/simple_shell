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
 * struct Alias - A structure to represent an alias in a shell
 * @alias_name: The name of the alias
 * @alias_value: The value associated with the alias
 * @next_alias: A pointer to the next alias in the list
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

char *custom_strdup(const char *src);

char *concat_strings(const char *str1, const char *str2);

int compare_strings(const char *string1, const char *string2, int match_mode);

int my_free_string_array(char **string_array);

char **split_string(const char *str, char delim, char **if_sep);

int my_list_length(char **list, const char *prefix);

char **my_copy_array(char **old_array, int new_size);

int my_free_array(char **array);

int my_setenv(const char *variable_name, const char *variable_value);

int my_unsetenv(const char *variable_name);

int my_change_directory(char *directory_name);

int my_alias_function(char **arguments, int to_free);

int free_alias_list(Alias *head);

int substitute_alias(char **command, Alias *alias_list);

int print_alias_list(Alias *alias_list);

int print_alias_value(char *argument, Alias *alias_list);

int update_alias_value(Alias *alias_list, const char *alias_name,
		const char *new_alias_value);

char *convert_int_to_string(int num);

int my_print_environment(void);

char *int_to_string(int number);

int string_to_int(const char *s);

#endif
