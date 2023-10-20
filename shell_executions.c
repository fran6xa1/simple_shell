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
		return (0); /* Return 0 to indicate failure*/
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
		if (WIFEXITED(status))
		{
			return ((WEXITSTATUS(status)) == 0);
/* Return 1 if child process exited successfully, 0 otherwise */
		}
		else
		{
			return (0); /* Return 0 if child process didn't exit normally */
		}
	}
	return (1); /* Return 1 to indicate success */
}

/**
 * findAlias - Find an alias by name in the AliasList.
 * @aliasList: A pointer to the AliasList.
 * @name: The name of the alias to search for.
 *
 * This function searches for an alias by name in the AliasList and returns
 * the corresponding value if found.
 *
 * Return: If found, a pointer to the alias value; otherwise, NULL.
 */
char *findAlias(const struct AliasList *aliasList, const char *name)
{
	struct Alias *temp = aliasList->head;

	while (temp != NULL)
	{
		if (strcmp(temp->name, name) == 0)
		{
			return (temp->value);
		}
		temp = temp->next;
	}
	return (NULL);
}

/**
 * addAlias - Add or update an alias in the AliasList.
 * @aliasList: A pointer to the AliasList.
 * @name: The name of the alias to add or update.
 * @value: The value of the alias.
 *
 * This function adds or updates an alias in the AliasList. If an alias with
 * the same name already exists, its value is updated; otherwise, a new alias
 * is created.
 */

void addAlias(struct AliasList *aliasList, const char *name, const char *value)
{

/* Check if the alias already exists and update its value */

	struct Alias *temp = aliasList->head;
	struct Alias *newAlias = malloc(sizeof(struct Alias));

	while (temp != NULL)
	{
	if (strcmp(temp->name, name) == 0)
	{
		free(temp->value);
		temp->value = strdup(value);
		return;
	}
	temp = temp->next;
	}
/*If the alias doesn't exist, create a new one */
	if (newAlias == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}
	newAlias->name = strdup(name);
	newAlias->value = strdup(value);
	newAlias->next = aliasList->head;
	aliasList->head = newAlias;
}

/**
 * printAliases - Print the aliases in the AliasList.
 * @aliasList: A pointer to the AliasList.
 *
 * This function prints the aliases
 * in the AliasList in the format 'name'='value'.
 */
void printAliases(const struct AliasList *aliasList)
{
	struct Alias *temp = aliasList->head;

	while (temp != NULL)
	{
		printf("%s='%s'\n", temp->name, temp->value);
		temp = temp->next;
	}
}
