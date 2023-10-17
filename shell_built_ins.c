#include "shell.h"

/**
 * my_setenv - Set an environment variable with a given name and value.
 * @variable_name: The name of the environment variable.
 * @variable_value: The value to set for the environment variable.
 *
 * Return: SKIP_FORK if successful, or an error code on failure.
 */
int my_setenv(const char *variable_name, const char *variable_value)
{
	char **new_environment;
	char *buffer;
	char *temp_buffer;
	char *existing_variable;
	int length;
	ssize_t bytes_written;

	if (variable_value == NULL)
	{
		bytes_written = write(STDERR_FILENO, "my_setenv: no value given\n", 26);
		(void)bytes_written;
		status = 2;
		return (SKIP_FORK);
	}

	buffer = concat_strings((char *)variable_name, "=");
	existing_variable = my_get_array_element(environ, buffer);

	temp_buffer = concat_strings(buffer, (char *)variable_value);
	free(buffer);
	buffer = temp_buffer;

	if (existing_variable == NULL)
	{
		length = my_list_length(environ, NULL);
		new_environment = my_copy_array(environ, length + 1);
		new_environment[length - 1] = buffer;
		new_environment[length] = NULL;
		my_free_array(environ);
		environ = new_environment;
		return (SKIP_FORK);
	}

	length = my_list_length(environ, (char *)variable_name);
	free(environ[length]);
	environ[length] = buffer;

	status = 0;

	return (SKIP_FORK);
}

/**
 * my_unsetenv - Unset an environment variable with the given name.
 * @variable_name: The name of the environment variable to unset.
 *
 * Return: SKIP_FORK if successful, or an error code on failure.
 */
int my_unsetenv(const char *variable_name)
{
	char **env_pointer;
	char *buffer;
	int index;
	ssize_t bytes_written;

	buffer = concat_strings((char *)variable_name, "=");
	index = my_list_length(environ, buffer);
	free(buffer);

	if (index == -1)
	{
		bytes_written = write(STDERR_FILENO, "my_unsetenv: variable not
				      found\n", 33);
		(void)bytes_written;
		status = 2;
				      return (SKIP_FORK);
	}

	env_pointer = environ + index;
	free(*env_pointer);

	while (*(env_pointer + 1) != NULL)
	{
		*env_pointer = *(env_pointer + 1);
		env_pointer++;
	}

	*env_pointer = NULL;
	status = 0;

	return (SKIP_FORK);
}

/**
 * my_change_directory - Change the current working directory.
 * @directory_name: The name of the directory to change to.
 *
 * Return: SKIP_FORK if successful, or an error code on failure.
 */
int my_change_directory(char *directory_name)
{
	char *home_directory;
	char *previous_working_directory;
	char old_path_buffer[PATH_MAX];
	char new_path_buffer[PATH_MAX];
	size_t buffer_size = PATH_MAX;
	int result;
	ssize_t bytes_written;

	if (getcwd(old_path_buffer, buffer_size) == NULL)
	{
		status = 2;
		return (SKIP_FORK);
	}

	if (directory_name == NULL)
	{
		home_directory = my_get_array_element(environ, "HOME=");
		if (home_directory == NULL)
		{
			status = 2;
			print_error_message("cd", directory_name);
			return (SKIP_FORK);
		}

		home_directory += 5;

		result = chdir((const char *)home_directory);
		if (result != -1)
			setenv("PWD", (const char *)home_directory, 1);
	}
	else if (compare_strings("-", directory_name, MATCH) == TRUE)
	{
		previous_working_directory = my_get_array_element(environ,
								  "OLDPWD=");
		if (previous_working_directory == NULL)
		{
			status = 2;
			print_error_message("cd", directory_name);
			return (SKIP_FORK);
		}

		previous_working_directory += 7;

		result = chdir((const char *)previous_working_directory);
		if (result != -1)
		{
			bytes_written = write(STDOUT_FILENO,
					      previous_working_directory,
					      custom_strlen(previous_working_
							    directory));
			(void)bytes_written;
			bytes_written = write(STDOUT_FILENO, "\n", 1);
			setenv("PWD", (const char *)
			       previous_working_directory, 1);
		}
	}
	else if (directory_name != NULL)
	{
		result = chdir((const char *)directory_name);
		if (result != -1)
			setenv("PWD", getcwd(new_path_buffer, buffer_size), 1);
	}

	if (result == -1)
	{
		status = 2;
		print_error_message("cd", directory_name);
		return (SKIP_FORK);
	}

	status = 0;
	setenv("OLDPWD", (const char *)old_path_buffer, 1);

	return (SKIP_FORK);
}
or = FALSE;
}
else
	{
		*char_pointer = '\0';
		char_pointer++;
		update_alias_value(&alias_head, *arguments, char_pointer);
		*(char_pointer - 1) = '=';
	}
arguments++;
}

if (no_error == FALSE)
	return (SKIP_FORK);

status = 0;
return (SKIP_FORK);
}

/**
 * my_print_environment - Print the environment variables.
 *
 * Return: SKIP_FORK if successful, or an error code on failure.
 */
int my_print_environment(void)
{
	char **env_pointer = environ;
	ssize_t bytes_written;
	ssize_t newline_written;

	while (*env_pointer != NULL)
	{
	    bytes_written = write(STDOUT_FILENO, *env_pointer,
				  custom_strlen(*env_pointer));
	    if (bytes_written == -1)
	    {
	    }

	    newline_written = write(STDOUT_FILENO, "\n", 1);
	    if (newline_written == -1)
	    {
	    }

	    env_pointer++;
	}

	status = 0;

	return (SKIP_FORK);
}
