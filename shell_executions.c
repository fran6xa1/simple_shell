#include "shell.h"

/**
 * executeCommand - executes commands entered by users
 *@command: command
 *@args: array of pointers to command arguments
 * Return: 0 on success, -1 on failure
 */
int executeCommand(char *command, char **args)
{
	pid_t child_pid;
	int status;
	char **environment = environ;

	child_pid = fork();
	if (child_pid < 0)
	{
	perror(command);
	return (-1); /* Return an error code */
	}
	if (child_pid == 0)
	{
	if (execve(command, args, environment) == -1)
	{
	perror(command);
	free(command);
	FreeBuffers(args);
	exit(98);
	}
	}
	else
	{
	wait(&status);
	}
	return (0); /* Return success */
}

