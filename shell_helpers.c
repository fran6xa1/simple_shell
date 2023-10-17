#include "shell.h"


/**
 * free_alias_list - Frees a linked list of aliases.
 * @head: A pointer to the head of the alias list.
 *
 * Return: 1 if successful, 0 if the head is NULL.
 */
int free_alias_list(Alias *head)
{
	Alias *current_alias, *next_alias;

	if (head == NULL)
		return (0);

	current_alias = head;
	while (current_alias != NULL)
	{
		next_alias = current_alias->next_alias;
		free(current_alias->alias_name);
		free(current_alias->alias_value);
		free(current_alias);
		current_alias = next_alias;
	}

	return (1);
}

/**
 * substitute_alias - Checks if a command matches an alias and substitutes it.
 * @command: A pointer to the command to check.
 * @alias_list: A linked list of aliases.
 *
 * Return: 1 if a substitution is made, 0 otherwise.
 */
int substitute_alias(char **command, Alias *alias_list)
{
	while (alias_list != NULL)
	{
		if (compare_strings(*command, alias_list->alias_name, MATCH) ==
		    TRUE)
		{
			*command = custom_strdup(alias_list->alias_value);
			return (1);
		}
		alias_list = alias_list->next_alias;
	}
	return (0);
}

/**
 * print_alias_list - Prints the aliases to STDOUT.
 * @alias_list: A linked list of aliases.
 *
 * Return: 1 to indicate successful printing.
 */
int print_alias_list(Alias *alias_list)
{
	while (alias_list != NULL)
	{
		ssize_t bytes_written_name = write(STDOUT_FILENO, alias_list->
						   alias_name, custom_strlen(alias_list->alias_name));
		ssize_t bytes_written_eq = write(STDOUT_FILENO, "=\'", 2);
		ssize_t bytes_written_value = write(STDOUT_FILENO, alias_list->
						    alias_value, custom_strlen(alias_list->alias_value));
		ssize_t bytes_written_newline = write(STDOUT_FILENO, "\'\n", 2);

		(void)bytes_written_name;
		(void)bytes_written_eq;
		(void)bytes_written_value;
		(void)bytes_written_newline;

		alias_list = alias_list->next_alias;
	}
	return (1);
}

/**
 * print_alias_value - Prints the value of an alias if found, or an error
 * message if not found.
 * @argument: The argument to search for in the alias list.
 * @alias_list: A linked list of aliases.
 *
 * Return: TRUE if the alias is found and printed, FALSE if not found.
 */

int print_alias_value(char *argument, Alias *alias_list)
{
	ssize_t bytes_written_alias, bytes_written_argument,
		bytes_written_not_found;

	while (alias_list != NULL)
	{
		fflush(stdin);
		if (compare_strings(argument, alias_list->alias_name, MATCH) ==
		    TRUE)
		{
			bytes_written_argument = write(STDOUT_FILENO, argument,
						       custom_strlen(argument));
			bytes_written_alias = write(STDOUT_FILENO, "=\'", 2);
			bytes_written_not_found = write(STDOUT_FILENO,
							alias_list->alias_value, custom_strlen(alias_list->alias_value));
			bytes_written_not_found = write(STDOUT_FILENO, "\'\n", 2);

			(void)bytes_written_argument;
			(void)bytes_written_alias;
			(void)bytes_written_not_found;

			return (TRUE);
		}
		alias_list = alias_list->next_alias;
	}

	bytes_written_alias = write(STDERR_FILENO, "alias: ", 7);
	bytes_written_argument = write(STDERR_FILENO, argument,
				       custom_strlen(argument));
	bytes_written_not_found = write(STDERR_FILENO, " not found\n", 11);

	(void)bytes_written_alias;
	(void)bytes_written_argument;
	(void)bytes_written_not_found;

	return (FALSE);
}

/**
 * update_alias_value - Sets the value of an existing alias or creates
 * a new one.
 * @alias_list: A pointer to the head of the alias list.
 * @alias_name: The name of the alias to update or create.
 * @new_alias_value: The new value to assign to the alias.
 *
 * Return: TRUE if successful, FALSE on failure.
 */
int update_alias_value(Alias *alias_list, char *alias_name,
		       char *new_alias_value)
{
	Alias *current_alias = alias_list;
	Alias *prev_alias = NULL;

	while (current_alias != NULL && compare_strings(current_alias->
							alias_name, alias_name, MATCH) != TRUE)
	{
	    prev_alias = current_alias;
	    current_alias = current_alias->next_alias;
	}

	if (current_alias != NULL)
	{
		free(current_alias->alias_value);
	}
	else
	{
		current_alias = (Alias *)malloc(sizeof(Alias));
		if (current_alias == NULL)
			exit(EXIT_FAILURE);

		current_alias->alias_name = custom_strdup(alias_name);
		current_alias->next_alias = NULL;

		if (prev_alias != NULL)
			prev_alias->next_alias = current_alias;
		else
			alias_list = current_alias;
	}

	current_alias->alias_value = custom_strdup(new_alias_value);

	return (TRUE);
}
