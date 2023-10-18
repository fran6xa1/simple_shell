#include "shell.h"

/**
 * my_get_array_element - Get an element from an array that matches a name
 * prefix.
 * @array: The array to search in.
 * @element_prefix: The prefix to match against elements in the array.
 *
 * Return: A pointer to the matching element, or NULL if not found.
 */
char *my_get_array_element(char **array, const char *element_prefix)
{
	int i;

	for (i = 0; array[i] != NULL; i++)
	{
		if (compare_strings(array[i], element_prefix, PREFIX) == TRUE)
		{
			return (array[i]);
		}
	}

	return (NULL);
}

/**
 * my_free_string_array - Free an array of strings and its memory.
 * @string_array: The array of strings to free.
 *
 * Return: TRUE if successful, FALSE if there's an error.
 */
int my_free_string_array(char **string_array)
{
	char **ptr = string_array;


	if (string_array == NULL)
	{
		return (FALSE);
	}

	ptr = string_array;

	while (*ptr != NULL)
	{
		free(*ptr);
		ptr++;
	}

	free(string_array);

	return (TRUE);
}

/**
 * split_string - Split a string into an array using a delimiter and return
 * the next position if it's a separator.
 * @str: The string to split.
 * @delim: The delimiter character.
 * @if_sep: Pointer to the position of the next character after a separator.
 *
 * Return: A dynamically allocated array of strings or NULL on memory
 * allocation failure.
 */
char **split_string(const char *str, char delim, char **if_sep);
char **split_string(const char *str, char delim, char **if_sep)
{
	const char *str_ptr = str;
	unsigned int i = 2;
	char **array = NULL;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == ';')
			break;
		if (*str_ptr == delim && *(str_ptr + 1) != '\0')
			i++;
		str_ptr++;
	}

	array = (char **)malloc(i * sizeof(char *));
	if (array == NULL)
	{
		return (NULL);
	}

	array[0] = (char *)str;
	str_ptr = str;
	i = 1;

	while (*str_ptr != '\0')
	{
		if (*str_ptr == delim)
		{
			str_ptr++;
			if (*str_ptr == ';')
			{
				array[i] = NULL;
				if (*(str_ptr + 1) != '\0' && *(str_ptr + 2)
				    != '\0')
				{
					*if_sep = (char *)(str_ptr + 2);
				}
				break;
			}
			if (*str_ptr != '\0')
			{
				array[i] = (char *)str_ptr;
				i++;
			}
		}
		str_ptr++;
	}
	array[i] = NULL;

	return (array);
}

/**
 * my_list_length - Calculate the length of a list with an optional prefix
 * match.
 * @list: The list to calculate the length of.
 * @prefix: The prefix to match against elements in the list
 * (or NULL for the full list).
 *
 * Return: The number of elements in the list or -1 if the prefix is not found.
 */
int my_list_length(char **list, const char *prefix)
{
	int length = 0;

	if (prefix == NULL)
	{
		while (*list != NULL)
		{
			length++;
			list++;
		}
	}
	else
	{
		while (*list != NULL)
		{
			if (compare_strings(*list, prefix, PREFIX) == TRUE)
			{
				return (length);
			}
			length++;
			list++;
		}
		return (-1);
	}

	return (length);
}

/**
 * my_copy_array - Copy an array of strings to a new array of the specified
 * size.
 * @old_array: The original array of strings to copy.
 * @new_size: The size of the new array.
 *
 * Return: A dynamically allocated new array of strings or NULL on memory
 * allocation failure.
 */
char **my_copy_array(char **old_array, int new_size)
{
	char **new_array;
	char **ptr_array;

	new_array = (char **)malloc(sizeof(char *) * new_size);
	if (new_array == NULL)
	{
		return (NULL);
	}

	ptr_array = new_array;

	while (*old_array != NULL)
	{
		*ptr_array = custom_strdup(*old_array);
		if (*ptr_array == NULL)
		{
			return (NULL);
		}
		ptr_array++;
		old_array++;
	}
	*ptr_array = NULL;

	return (new_array);
}
