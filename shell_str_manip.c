A#include "shell.h"

/**
 * CompareStrings - Compares two strings.
 * @str1: String to be compared with str2.
 * @str2: String to be compared with str1.
 *
 * Return: 0 if strings are equal, positive value if str1 > str2,
 * negative value if str1 < str2.
 */
int CompareStrings(char *str1, char *str2)
{
	while (*str1 && (*str1 == *str2))
	{
		str1++;
		str2++;
	}

	return (*(unsigned char *)str1 - *(unsigned char *)str2);
}
/**
 * StringLength - Returns the length of a string.
 * @str: String passed.
 *
 * Return: Length of the string passed.
 */
int StringLength(char *str)
{
	int length = 0;

	while (*str != '\0')
	{
		length++;
		str++;
	}

	return (length);
}

/**
 * CompareStringsN - Compares two strings up to n bytes.
 * @str1: String to be compared with str2.
 * @str2: String to be compared with str1.
 * @n: Number of bytes to compare.
 *
 * Return: 0 if strings are equal up to n bytes, positive value if str1 > str2,
 * negative value if str1 < str2.
 */
int CompareStringsN(char *str1, char *str2, int n)
{
	int i;

	for (i = 0; str1[i] && str2[i] && i < n; i++)
	{
		if (str1[i] != str2[i])
			return (str1[i] - str2[i]);
	}

	return (0);
}

/**
 * DuplicateString - Duplicates a string.
 * @source: String to be duplicated.
 *
 * Return: Pointer to the newly allocated duplicated string.
 * NULL if memory allocation fails or input string is NULL.
 */
char *DuplicateString(char *source)
{
	int length;
	char *duplicate;
	int i;

	if (source == NULL)
		return (NULL);

	length = 0;
	while (source[length] != '\0')
	{
		length++;
	}

	duplicate = (char *)malloc(sizeof(char) * (length + 1));

	if (duplicate == NULL)
	{
		return (NULL); /* Memory allocation failed */
	}

	for (i = 0; i <= length; i++)
	{
		duplicate[i] = source[i];
	}

	return (duplicate);
}

/**
 * FindCharacter - Locates a character in a string.
 * @str: String to be checked.
 * @ch: Character to be located.
 *
 * Return: Returns a pointer to the first occurrence of the character
 * or NULL if the character is not found.
 */
char *FindCharacter(char *str, char ch)
{
	while (*str != '\0')
	{
		if (*str == ch)
			return (str);
		str++;
	}

	if (ch == '\0')
		return (str);

	return (NULL);
}
