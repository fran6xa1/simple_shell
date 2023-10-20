#ifndef SHELL_H
#define SHELL_H

#include <stdarg.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <time.h>
#include <stdbool.h>
#include <signal.h>

/* environment variables */
extern char **environ;

/* handle built ins */
int evaluateCommand(char **arguments, char *inputLine);
void DisplayPrompt(void);
void HandleSignal(int sigNum);
char **TokenizeInput(char *input);
char *ValidatePath(char **directories, char *command);
char *concatPaths(char *base, char *cmd);
int CheckBuiltin(char **cmd, char *inputLine);
void HandleExit(char **cmd, char *input);

void DisplayEnvironment(void);

/* string handlers */
char *StringCopy(char *dest, const char *src);
int CompareStrings(char *str1, char *str2);
int StringLength(char *str);
int CompareStringsN(char *str1, char *str2, int n);
char *DuplicateString(char *source);
char *FindCharacter(char *str, char ch);

int executeCommand(char *command, char **args);
char *GetPath(void);

/* helper function for efficient free */
void FreeBuffers(char **arr);


extern struct builtin
{
	char *env;
	char *exit;
} builtin;

#endif
