#include "shell.h"

/**
* concatPaths - concatenates path and command
* @base: base path of the command
* @cmd: user entered command
*
* Return: buffer containing concatenated path and command on success
* NULL on failure
*/
char *concatPaths(char *base, char *cmd)
{
	char *res;
	size_t baseLen = 0, cmdLen = 0;
	size_t i;
	size_t j;

	if (cmd == NULL)
		cmd = "";

	if (base == NULL)
		base = "";

  /* Calculates the length of base path and user command */
	while (base[baseLen] != '\0')
		baseLen++;

	while (cmd[cmdLen] != '\0')
		cmdLen++;

	/* Allocate memory for the result buffer */
	res = malloc(sizeof(char) * (baseLen + cmdLen + 2));
	if (res == NULL)
		return (NULL);

	/* Copy base path to the result buffer */
	for (i = 0; i < baseLen; i++)
		res[i] = base[i];

	/* If base path doesn't end with '/', add '/' */
	if (baseLen > 0 && base[baseLen - 1] != '/')
	{
		res[baseLen] = '/';
		baseLen++;
	}

	/* Copy user command to the result buffer */
	for (j = 0; j < cmdLen; j++)
		res[baseLen + j] = cmd[j];
	/* Null-terminate the result buffer */
	res[baseLen + cmdLen] = '\0';
	return (res);
}

/**
 * Custom strcpy - Copies a string from source to destination.
 * @dest: Destination string.
 * @src: Source string.
 * Return: Pointer to the destination string.
 */
char *StringCopy(char *dest, const char *src)
{
	char *start = dest;

	while (*src != '\0')
	{
		*dest = *src;
		dest++;
		src++;
	}
	*dest = '\0';
	return (start);
}

/**
 * evaluateCommand - determines whether it's a built-in or external command
 * @arguments: tokenized user input
 * @inputLine: line obtained from getline function
 * Return: 1 if the command is executed, 0 if not
 */
int evaluateCommand(char **arguments, char *inputLine)
{
	if (CheckBuiltin(arguments, inputLine))
	{
		return (1);
	}
	else if (**arguments == '/')
	{
		executeCommand(arguments[0], arguments);
		return (1);
	}
	return (0);
}

/**
 * GetPath - Finds the PATH from the global environment variables.
 * Return: NULL if PATH is not found, or PATH if found.
 */
char *GetPath(void)
{
	char **envVar = environ;
	char *path = NULL;

	while (*envVar != NULL)
	{
		if (CompareStringsN(*envVar, "PATH=", 5) == 0)
		{
			path = malloc(StringLength(*envVar) - 4);
			if (path == NULL)
			{
				perror("Memory allocation error");
				exit(EXIT_FAILURE);
			}

			StringCopy(path, *envVar + 5);
			return (path);
		}
		envVar++;
	}

	return (NULL);
}
/**
 * ValidatePath - Checks whether path is valid and contains the command.
 * @directories: Tokenized directories in the PATH.
 * @command: User entered command.
 *
 * Return: Full path to the command if found, NULL on failure.
 */
char *ValidatePath(char **directories, char *command)
{
	int index = 0;
	char *fullPath = NULL;

	while (directories[index] != NULL)
	{
		size_t len = snprintf(NULL, 0, "%s/%s", directories[index], command) + 1;

		fullPath = malloc(len);
		if (fullPath == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}
		snprintf(fullPath, len, "%s/%s", directories[index], command);

		if (access(fullPath, F_OK | X_OK) == 0)
		{
			return (fullPath);
		}

		free(fullPath);
		index++;
	}

	return (NULL);
}
