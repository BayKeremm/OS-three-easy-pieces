#ifndef INPUT_HANDLER
#define INPUT_HANDLER

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

int getUserInput(char ** lineptr, size_t * n, FILE * stream);


#endif