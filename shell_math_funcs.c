#include "shell.h"

/**
 * int_to_string - Converts an integer into a string.
 * @number: Integer to be converted.
 *
 * Return: The converted string.
 */
char *int_to_string(int number)
{
	char *str;
	int size = snprintf(NULL, 0, "%d", number);

	if (size < 0)
	{
		perror("snprintf");
		exit(EXIT_FAILURE);
	}

	str = malloc(size + 1);
	if (str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	snprintf(str, size + 1, "%d", number);
	return (str);
}

/**
 * string_to_int - Converts a string into an integer.
 * @s: String to be converted.
 *
 * Return: The converted integer.
 */
int string_to_int(const char *s)
{
	int result = 0;
	int sign = 1;

	if (*s == '-')
	{
		sign = -1;
		s++;
	}

	while (*s != '\0')
	{
		if (isdigit(*s))
		{
			result = (result * 10) + (*s - '0');
		}
		else
		{
			return (-1);
		}
		s++;
	}

	return (result * sign);
}

/**
 * my_free_array - Free an array of strings and its memory.
 * @array: The array of strings to free.
 *
 * Return: TRUE if successful.
 */
int my_free_array(char **array)
{
	int i;

	if (array == NULL)
	{
		return (FALSE);
	}

	for (i = 0; array[i] != NULL; i++)
	{
		free(array[i]);
	}

	free(array);

	return (TRUE);
}

/**
 * convert_int_to_string - Converts an integer to a string.
 * @num: Integer to be converted.
 *
 * Return: The converted string.
 */
char *convert_int_to_string(int num)
{
	char *str;
	int length = snprintf(NULL, 0, "%d", num);

	str = malloc(length + 1);

	if (str == NULL)
	{
		perror("malloc");
		exit(EXIT_FAILURE);
	}
	snprintf(str, length + 1, "%d", num);
	return (str);
}
