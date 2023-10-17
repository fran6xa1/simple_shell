#include "shell.h"

/**
 * handle_commands - Manages command execution and control flow
 * using logical operators
 * @args: An array of strings representing the command and its arguments
 *
 * Return:
 *  - 1 on successful execution without errors
 *  - 0 on errors or if a command fails
 */
int handle_commands(char **args)
{
	char **args_ptr = args;
	int prev_eval = 0; /* NEITHER replaced with 0 */
	int no_error = 1; /* TRUE replaced with 1 */
	char prev_op = 'c';
	char next_op = 'c';
	int command_result = 0;

	while (*args != NULL && prev_eval != 2) /* EXIT_SHELL replaced with 2 */
	{
		while (*args_ptr != NULL && **args_ptr != '&' && **args_ptr != '|')
			args_ptr++;

		if (compare_strings(*args_ptr, "||", MATCH) == 1) /* TRUE replaced with 1 */
		{
			*args_ptr = NULL;
			args_ptr++;
			next_op = '|';
		}
		if (compare_strings(*args_ptr, "&&", MATCH) == 1) /* TRUE replaced with 1 */
		{
			*args_ptr = NULL;
			args_ptr++;
			next_op = '&';
		}
		if (next_op == 'c')
			break;

		prev_eval = and_or(args, prev_op, prev_eval);
		if (prev_eval == 0) /* FALSE replaced with 0 */
			no_error = 0; /* FALSE replaced with 0 */
		prev_op = next_op;
		args = args_ptr;
	}

	if (next_op == 'c')
	{
		command_result = execute_command(args);

		if (command_result == 2) /* EXIT_SHELL replaced with 2 */
			return (2); /* EXIT_SHELL replaced with 2 */
	}

	if (no_error == 0 || command_result == 0) /* TRUE and FALSE swapped */
		return (0); /* FALSE replaced with 0 */

	return (1); /* TRUE replaced with 1 */
}

/**
 * built_ins - checks if a command is a built in
 * @args: command and arguments
 *
 * Return: SKIP_FORK if built in, DO_EXECVE if not a built in, EXIT_SHELL if
 * exit shell, EXIT_SHELL_CODE if exiting with a particular code
 */
int built_ins(char **args)
{
	char **args_ptr = args;
	int i;

	while (*args_ptr != NULL)
	{
		if (**args_ptr == '#')
		{
			*args_ptr = NULL;
			break;
		}
		if (compare_strings("~", *args_ptr, MATCH) == TRUE
		    && my_get_array_element(environ, "HOME=") != NULL)
		{
			*args_ptr = custom_strdup(my_get_array_element
					(environ, "HOME=") + 5);
			continue;
		}
		if (compare_strings("~/", *args_ptr, PREFIX) == TRUE
		    && my_get_array_element(environ, "HOME=") != NULL)
		{
			*args_ptr = concat_strings(my_get_array_element
					       (environ, "HOME=")
					       + 5, *args_ptr + 1);
		}
		*args_ptr = evaluate_variables(*args_ptr);

		args_ptr++;
	}
	if (*args == NULL)
		return (SKIP_FORK);

	i = my_alias_function(args, FALSE);
	if (i == DO_EXECVE || i == SKIP_FORK)
		return (i);

	if (compare_strings("exit", *args, MATCH) == TRUE && args[1] != NULL)
	{
		status = string_to_int(args[1]);
		if (status < 0)
		{
			status = 2;
			print_error_message(args[0], args[1]);
			return (SKIP_FORK);
		}
	}
	if (compare_strings("exit", *args, MATCH) == TRUE)
		return (EXIT_SHELL);
	else if (compare_strings("setenv", *args, MATCH) == TRUE && args[1] != NULL)
		return (my_setenv(args[1], args[2]));
	else if (compare_strings("unsetenv", *args, MATCH) == TRUE
		 && args[1] != NULL)
		return (my_unsetenv(args[1]));
	else if (compare_strings("cd", *args, MATCH) == TRUE)
		return (my_change_directory(args[1]));
	else if (compare_strings("env", *args, MATCH) == TRUE)
		return (my_print_environment());

	return (DO_EXECVE);
}

/**
 * and_or - deals with command line logical operators
 * @args: command and arguments
 * @operator: first char of logical operator
 * @last_compare: if last command in logic evaluated to true or false
 *
 * Return: if this command evaluates to true or false
 */
int and_or(char **args, char operator, int last_compare)
{
	int i;

	if (last_compare == NEITHER)
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}
	if (last_compare == TRUE && operator == '&')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (last_compare == FALSE && operator == '|')
	{
		i = execute_command(args);
		if (i == EXIT_SHELL)
			return (EXIT_SHELL);
		if (i == TRUE)
			return (TRUE);

		return (FALSE);
	}

	if (last_compare == TRUE && operator == '|')
		return (TRUE);

	return (FALSE);
}

/**
 * find_executable_path - Finds the full path of an executable command.
 * @args: The command and its arguments.
 *
 * Return:
 *  - Full path of the executable if found, otherwise NULL.
 */
char *find_executable_path(char **args)
{
	char *command_name = *args;
	char *path_env;
	char *path_copy;
	char *path;
	char *token;
	char *full_path;

		if (access(command_name, X_OK) == 0)
	{
		return (custom_strdup(command_name));
	}

	path_env = getenv("PATH");
	if (path_env == NULL)
	{
		fprintf(stderr, "Error: PATH environment variable not found.\n");
		return (NULL);
	}

	path_copy = custom_strdup(path_env);
	path = path_copy;
	token = strtok(path, ":");

		while (token != NULL)
	{
		full_path = malloc(strlen(token) + strlen(command_name) + 2);

		if (full_path == NULL)
		{
			fprintf(stderr, "Error: Memory allocation failed.\n");
			free(path_copy);
			return (NULL);
		}

		strcpy(full_path, token);
		strcat(full_path, "/");
		strcat(full_path, command_name);

		if (access(full_path, X_OK) == 0)
		{
			free(path_copy);
			return (full_path);
		}

		free(full_path);
		token = strtok(NULL, ":");
	}

	fprintf(stderr, "Error: Command '%s' not found in PATH.\n", command_name);
	free(path_copy);
	return (NULL);
}


/**
 * execute_command - executes a command
 * @args: command and arguments
 *
 * Return: TRUE or EXIT_SHELL
 */
int execute_command(char **args)
{
	char *buf_ptr = *args;
	char *command_name;
	pid_t pid;
	int what_do = built_ins(args);

	if (what_do == DO_EXECVE)
	{
		command_name = find_executable_path(args);
		if (command_name == NULL)
			return (FALSE);

		pid = fork();
		if (pid == -1)
		{
			exit(EXIT_FAILURE);
		}
		if (pid == 0)
		{
			execve(command_name, args, environ);
			exit(EXIT_FAILURE);
		}
		wait(&status);
		free(command_name);
		fflush(stdin);
		if (status != 0)
		status = 2;
	}

	if (compare_strings("false", *args, MATCH) == TRUE)
		status = 1;

	if (*args != buf_ptr)
		free(*args);
	args++;

	while (*args != NULL)
	{
		while (*buf_ptr != '\0')
		{
			buf_ptr++;
		}
		buf_ptr++;

		if (*args != buf_ptr)
			free(*args);

		args++;
	}

	if (what_do == EXIT_SHELL)
		return (EXIT_SHELL);

	if (status != 0)
		return (FALSE);

	return (TRUE);
}
