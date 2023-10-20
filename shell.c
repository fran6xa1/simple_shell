#include "shell.h"
/**
* main - carries out the read, execute then print output loop
* @ac: argument count
* @av: argument vector
* @envp: environment vector
*
* Return: 0
*/
struct info
{
	int final_exit;
	int ln_count;
} info;

struct flags
{
	bool interactive;
} flags;

int main(int ac, char **av, char *envp[]);
int main(int ac, char **av, char *envp[])
{
	char *line = NULL, *pathcommand = NULL, *path = NULL;
	size_t bufsize = 0;
	ssize_t linesize = 0;
	char **command = NULL, **paths = NULL;
	(void)envp, (void)av;
	if (ac < 1)
		return (-1);
	signal(SIGINT, HandleSignal);
	while (1)
	{
		FreeBuffers(command);
		FreeBuffers(paths);
		free(pathcommand);
		DisplayPrompt();
		linesize = getline(&line, &bufsize, stdin);
		if (linesize < 0)
			break;
		info.ln_count++;
		if (line[linesize - 1] == '\n')
			line[linesize - 1] = '\0';
		command = TokenizeInput(line);
		if (command == NULL || *command == NULL || **command == '\0')
			continue;
		if (evaluateCommand(command, line))
			continue;
		path = GetPath();
		paths = TokenizeInput(path);
		pathcommand = ValidatePath(paths, command[0]);
		if (!pathcommand)
			perror(av[0]);
		else
			executeCommand(pathcommand, command);
	}
	if (linesize < 0 && flags.interactive)
	{
		if (write(STDERR_FILENO, "\n", 1) == -1)
		{
		}
	}
	free(line);
	return (0);
}
