#include "shell.h"

/**
* _putchar - writes the character c to stdout
* @x: The character to print
*
* Return: On success 1.
* On error, -1 is returned and errno set appropriately
*/
int _putchar(char x)
{
	return (write(1, &x, 1));
}

/**
 * DisplayString - Prints a string to standard output.
 * @str: String to be printed.
 * Return: Number of characters printed.
 */
int DisplayString(char *str)
{
	int charCount = 0;

	while (*str != '\0')
	{
		if (write(STDOUT_FILENO, str, 1) == -1)
		{
			/* Handle the write error here, if necessary */
			return (-1); /* Indicate an error */
		}
		str++;
		charCount++;
	}

	return (charCount);
}

