#ifndef PARSING_HANDLER
#define PARSING_HANDLER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "utils.h"

void parseInput(char ** myArgs, char * lineptr, int maxArgs);

int checkBuiltIn(char * command);
//int executeBuiltIn(int command, char ** myArgs);

#endif