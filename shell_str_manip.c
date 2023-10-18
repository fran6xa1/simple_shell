#include "shell.h"

/**
 *  custom_strlen - returns length of a string
 * @str: string to be evaluated
 *
 * Return: the length of the string
 */
	size_t custom_strlen(const char *str)
{
	size_t length;

	if (str == NULL)
	{
		return (0);
	}

	length = 0;

	while (str[length] != '\0')
	{
		length++;
	}

	return (length);
}


/**
 * custom_strdup - allocates a space in memory for a copy of a string
 * @src: string a copy is made of
 *
 * Return: a pointer to the copy, or NULL if failure
 */
	char *custom_strdup(const char *src)
{
	size_t len;
	size_t i;
	char *dest;

	if (src == NULL)
	{
		return (NULL);
	}

	len = custom_strlen(src);
	dest = (char *)malloc(len + 1);

	if (dest == NULL)
	{
		return (NULL);
	}

	for (i = 0; i <= len; i++)
	{
		dest[i] = src[i];
	}

	return (dest);
}

/**
 * concat_strings - concatenates two strings
 * @str1: first string
 * @str2: second string
 *
 * Return: a pointer to the new string, or NULL if failure
 */
char *concat_strings(const char *str1, const char *str2);
char *concat_strings(const char *str1, const char *str2)
{
	size_t len1;
	size_t len2;
	size_t total_len;
	char *result;
	char *dest;

	if (str1 == NULL && str2 == NULL)
	{
		return (NULL);
	}

	len1 = (str1 != NULL) ? custom_strlen(str1) : 0;
	len2 = (str2 != NULL) ? custom_strlen(str2) : 0;
	total_len = len1 + len2;

	result = (char *)malloc(total_len + 1);
	if (result == NULL)
	{
		return (NULL);
	}

	dest = result;

	if (str1 != NULL)
	{
		while (*str1 != '\0')
		{
			*dest = *str1;
			dest++;
			str1++;
		}
	}

	if (str2 != NULL)
	{
		while (*str2 != '\0')
		{
			*dest = *str2;
			dest++;
			str2++;
		}
	}

	*dest = '\0';

	return (result);
}

/**
 * compare_strings - compare two string
 * @string1: string to be compared
 * @string2: string to be compared
 * @match_mode: if string needs to be matched exactly or if just a prefix
 * needs to be matched
 *
 * Return: difference between strings
 */
	int compare_strings(const char *string1, const char *string2, int match_mode)
{
	int i;

	if (string1 == NULL || string2 == NULL)
		return (0);

	if (match_mode == 0)
	{
		return (0);
	}

	i = 0;

	while (string1[i] != '\0' && string2[i] != '\0')
	{
		if (string1[i] != string2[i])
			return (0);

		i++;
	}

	if (match_mode == 1 || (string1[i] == '\0' && string2[i] == '\0'))
		return (1);

	return (0);
}
