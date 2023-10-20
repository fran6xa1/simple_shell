#include "shell.h"

/**
* CheckBuiltin - checks if the command is a built-in function and executes it
* @cmd: tokenized commands
* @inputLine: input read from stdin
*
* Return: 1 if executed, 0 if not
*/
int CheckBuiltin(char **cmd, char *inputLine)
{
	struct BuiltIn
	{
		char *env;
		char *exit;
	} commands = {"env", "exit"};

	if (CompareStrings(*cmd, commands.env) == 0)
	{
		DisplayEnvironment();
		return (1);
	}
	else if (CompareStrings(*cmd, commands.exit) == 0)
	{
		HandleExit(cmd, inputLine);
		return (1);
	}
	return (0);
}

/**
 * HandleExit - Handles the exit command.
 * @cmd: Tokenized command.
 * @input: Input read from stdin.
 *
 * This function frees memory and exits the program.
 */
void HandleExit(char **cmd, char *input)
{
	free(input);
	FreeBuffers(cmd);
	exit(0);
}

/**
 * FreeBuffers - Frees memory allocated for buffers.
 * @arr: Array of pointers to buffers to be freed.
 *
 * This function takes an array of pointers to buffers and frees the memory
 * allocated for each buffer and the array itself.
 */
void FreeBuffers(char **arr);
void FreeBuffers(char **arr)
{
	int i;
	char *buf;

	if (arr == NULL || *arr == NULL)
	{
		return; /* No memory allocated, nothing to free */
	}

	i = 0;
	buf = arr[i];

	while (buf != NULL)
	{
		free(buf); /* Free individual buffer */
		i++;
		buf = arr[i];
	}

	free(arr); /* Free the array of pointers to buffers */
}

/**
 * HandleSignal - Handles signals to track interactive mode.
 * @sigNum: The signal number.
 *
 * This function handles signals and maintains interactive mode.
 */
void HandleSignal(int sigNum)
{
	(void)sigNum; /* Unused parameter */
	if (write(STDERR_FILENO, "\n", 1) == -1)
	{
	}
	if (write(STDERR_FILENO, "$", 1) == -1)
	{
	}
}

struct flags
{
	bool interactive;
} flag;
/**
 * DisplayPrompt - Displays the shell prompt if in interactive mode.
 *
 * This function checks if the shell is in interactive mode and prints
 * the shell prompt accordingly.
 */
void DisplayPrompt(void)
{
	if ((isatty(STDIN_FILENO) == 1) && (isatty(STDOUT_FILENO) == 1))
	{
		flag.interactive = 1; /* Assume flags is a global variable */
		if (flag.interactive)
		{
			if (write(STDERR_FILENO, "> ", 2) == -1)
			{
				/* Handle the write error here, if necessary */
			}
		}
	}
}
