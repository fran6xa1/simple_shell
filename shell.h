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

/* environment variables */
extern char **environ;
extern __sighandler_t signal(int __sig, __sighandler_t __handler);

/* handle built ins */
int evaluateCommand(char **arguments, char *inputLine);
void DisplayPrompt(void);
void HandleSignal(int sigNum);
char **TokenizeInput(char *input);
char *ValidatePath(char **directories, char *command);
char *concatPaths(char *base, char *cmd);
int CheckBuiltin(char **cmd, char *inputLine);
void HandleExit(char **cmd, char *input);

