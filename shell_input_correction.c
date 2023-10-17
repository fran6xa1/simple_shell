#include "shell.h"

/**
 * sanitize_input - Sanitizes input from the command line.
 * @input_buffer: Buffer to be sanitized.
 * @input_size: Size of input buffer.
 *
 * Return: The new, sanitized buffer.
 */
char *sanitize_input(char *input_buffer, size_t *input_size)
{
	size_t input_index = 0;
	size_t sanitized_index = 0;
	int is_space = 1;
	char *sanitized_buffer = malloc(*input_size);

	if (sanitized_buffer == NULL)
	{
		return (NULL);
	}

	while (input_index < *input_size)
	{
		char current_char = input_buffer[input_index];

		if (current_char == ' ' || current_char == ';' ||
			current_char == '|' || current_char == '&')
		{
			if (!is_space)
			{
				sanitized_buffer[sanitized_index] = ' ';
				sanitized_index++;
				is_space = 1;
			}

			sanitized_buffer[sanitized_index] = current_char;
			sanitized_index++;
			input_index++;
		}
		else
		{
			sanitized_buffer[sanitized_index] = current_char;
			sanitized_index++;
			input_index++;
			is_space = 0;
		}
	}

	sanitized_buffer[sanitized_index] = '\0';
	*input_size = sanitized_index + 1;

	free(input_buffer);
	return (sanitized_buffer);
}


/**
 * has_unexpected_chars - Checks if the input contains unexpected characters.
 * @input: Input string to be checked.
 *
 * Return: 1 if no unexpected characters found, 0 otherwise.
 */
int has_unexpected_chars(const char *input)
{
	const char *ptr = input;
	const char *next_char;

	while (*ptr != '\0')
	{
		if (*ptr == ';' || *ptr == '|' || *ptr == '&')
		{
			next_char = ptr + 1;
			while (*next_char == *ptr)
			{
				next_char++;
			}
			if (*next_char == ';' || *next_char == '|' ||
					*next_char == '&' || *next_char == ' ')
			{
				return (0);
			}
		}
		ptr++;
	}
	return (1);
}


/**
 * print_error_message - Prints error messages and sets status.
 * @command: Command causing the error.
 * @argument: First argument to the command.
 */
void print_error_message(const char *command, const char *argument)
{
	char *line_number_str;
	ssize_t write_result;

	line_number_str = convert_int_to_string(line_num);

	write_result = write(STDERR_FILENO, shell_name, custom_strlen(shell_name));
	if (write_result == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	write_result = write(STDERR_FILENO, ": ", 2);
	if (write_result == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	write_result = write(STDERR_FILENO, line_number_str,
			custom_strlen(line_number_str));
	free(line_number_str);
	if (write_result == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	if (compare_strings("cd", command, MATCH) == TRUE)
	{
		status = 2;
		write_result = write(STDERR_FILENO, ": cd: can't cd to ", 18);
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		write_result = write(STDERR_FILENO, argument,
				custom_strlen((char *)argument));
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		write_result = write(STDERR_FILENO, "\n", 1);
		if (write_result == -1)
		{
		perror("write");
			exit(EXIT_FAILURE);
		}
		return;
	}

	if (compare_strings("exit", command, MATCH) == TRUE)
	{
		write_result = write(STDERR_FILENO, ": exit: Illegal number: ", 24);
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		write_result = write(STDERR_FILENO,
				argument, custom_strlen((char *)argument));
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		write_result = write(STDERR_FILENO, "\n", 1);
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		return;
	}

	if (*command == ';' || *command == '|' || *command == '&')
	{
		status = 2;
		write_result = write(STDERR_FILENO, ": Syntax error: \"", 17);
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		write_result = write(STDERR_FILENO, command, 1);
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		if (*command == *(command + 1))
			write_result = write(STDERR_FILENO, command, 1);
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}

		write_result = write(STDERR_FILENO, "\" unexpected\n", 14);
		if (write_result == -1)
		{
			perror("write");
			exit(EXIT_FAILURE);
		}
		return;
	}

	status = 127;
	write_result = write(STDERR_FILENO, ": ", 2);
	if (write_result == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	write_result = write(STDERR_FILENO, command, custom_strlen((char *)command));
	if (write_result == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	write_result = write(STDERR_FILENO, ": not found\n", 12);
	if (write_result == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}
}


/**
 * evaluate_variables - Evaluates variables in the given argument.
 * @argument: Argument to be checked and evaluated.
 *
 * Return: A pointer to the evaluated argument.
 */
char *evaluate_variables(const char *argument)
{
	char *evaluated_argument = strdup(argument);
	char *ptr = evaluated_argument;
	char *start = NULL;
	size_t var_length = 0;
	char *var_name;
	char *replacement;
	size_t prefix_length;
	size_t suffix_length;
	char *prefix;
	char *suffix;
	const char *env_value;

	while (*ptr != '\0')
	{
		if (*ptr == '$')
		{
			start = ptr + 1;
			while (*ptr != '\0' && *ptr != ' ' && *ptr != '\t')
			{
				ptr++;
			}
			var_length = ptr - start;
			var_name = malloc(var_length + 1);
			if (var_name == NULL)
			{
				perror("malloc");
				exit(EXIT_FAILURE);
			}
			strncpy(var_name, start, var_length);
			var_name[var_length] = '\0';

			env_value = getenv(var_name);
			free(var_name);

			if (env_value != NULL)
			{
				replacement = strdup(env_value);
				prefix_length = start - evaluated_argument - 1;
				suffix_length = custom_strlen(ptr);
				prefix = strndup(evaluated_argument, prefix_length);
				suffix = strdup(ptr);
				free(evaluated_argument);
				evaluated_argument = malloc(prefix_length
						+ custom_strlen(replacement) + suffix_length + 1);
				if (evaluated_argument == NULL)
				{
					perror("malloc");
					exit(EXIT_FAILURE);
				}
				snprintf(evaluated_argument, prefix_length + 1, "%s", prefix);
				strcat(evaluated_argument, replacement);
				strcat(evaluated_argument, suffix);
				free(prefix);
				free(suffix);
				free(replacement);
				ptr = evaluated_argument + prefix_length;
			}
		}
		ptr++;
	}

	return (evaluated_argument);
}

