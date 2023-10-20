#include "shell.h"

/**
 * TokenizeInput - Creates tokens from given input.
 * @input: Input to be tokenized.
 *
 * Return: Array of strings representing tokens.
 */
char **TokenizeInput(char *input);
char **TokenizeInput(char *input)
{
	char *token = NULL, *delim = " \t\r\n";
	char **tokens = NULL;
	int tokensize = 1;
	size_t index = 0;
	int flag = 0;
	char *inputCopy = DuplicateString(input);
	size_t inputLength;
	size_t i;

	if (inputCopy == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	inputLength = StringLength(inputCopy);

	for (i = 0; i < inputLength; i++)
	{
		if (CompareStringsN(delim, inputCopy + i, 1) == 0 && flag == 0)
		{
			tokensize++;
			flag = 1;
		}
		else if (CompareStringsN(delim, inputCopy + i, 1) != 0 && flag == 1)
		{
			flag = 0;
		}
	}

	free(inputCopy);

	tokens = (char **)malloc(sizeof(char *) * (tokensize + 1));

	if (tokens == NULL)
	{
		perror("Memory allocation error");
		exit(EXIT_FAILURE);
	}

	token = strtok(input, delim);

	while (token != NULL)
	{
		tokens[index] = DuplicateString(token);

		if (tokens[index] == NULL)
		{
			perror("Memory allocation error");
			exit(EXIT_FAILURE);
		}

		token = strtok(NULL, delim);
		index++;
	}

	tokens[index] = NULL;
	return (tokens);
}
