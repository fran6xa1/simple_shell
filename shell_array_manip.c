#include "shell.h"

/**
 * DisplayEnvironment - Prints the environment strings to stdout.
 *
 * This function prints the environment strings to the standard output.
 */

void DisplayEnvironment(void)
{
	char **envVar = environ;
	int index = 0;
	char *currentEnv;

	while (envVar[index] != NULL)
	{
		currentEnv = envVar[index];
		while (*currentEnv != '\0')
		{
			if (write(STDOUT_FILENO, currentEnv, 1) == -1)
			{
				/* Handle the write error here, if necessary */
			}
			currentEnv++;
		}
		if (write(STDOUT_FILENO, "\n", 1) == -1)
		{
			/* Handle the write error here, if necessary */
		}
		index++;
	}
}

