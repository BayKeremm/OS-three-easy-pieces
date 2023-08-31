#include "parsing_handler.h"
void parseInput(char ** myArgs, char * lineptr, int maxArgs){
    lineptr[strcspn(lineptr,"\n")] = ' ';
    char * token = strtok(lineptr, " ");
    int argIndex = 0;

    while(token != NULL && argIndex < maxArgs -1){
        myArgs[argIndex] = token;
        argIndex++;
        token = strtok(NULL," ");
    }
    myArgs[argIndex] = NULL;
}


int checkBuiltIn(char * command){
    // BUILT IN COMMAND CHECKS
    if(strcmp(command,"exit") == 0){
        return COMMAND_EXIT;
    }

    if(strcmp(command,"cd") == 0){
        return COMMAND_CD;
    }

    if(strcmp(command,"path") == 0){
        return COMMAND_PATH;
    }
    return 0;
}

//int executeBuiltIn(int command, char ** myArgs){

    //return 0;
//}