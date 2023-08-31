#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>
#include "input_handler.h"
#include "parsing_handler.h"
#include"utils.h"


int main(int argc, char * argv[])
{
    if(argc > 2){
        perror("Wrong usage of the shell, either invoke it alone or pass commands file");
        exit(1);
    }

    char *additional_paths = "."; // Add your additional paths here
    char * original_path = getenv("PATH");
    char *new_path = (char *)malloc(strlen(original_path) + strlen(additional_paths) + 2);

    if (new_path == NULL) {
        perror("Memory allocation failed");
        exit(1);
    }

    sprintf(new_path, "%s:%s", additional_paths, original_path);

    char *path_copy = strdup(new_path);

    char * line;
    size_t n = 100;

    line = (char *) malloc(n * sizeof(char));

    if (line == NULL){
        printf("Unable to allocate buffer\n");
        return 1;
    }
    char alive = 1;
    while(alive){
        printf("wish> ");

        getUserInput(&line, &n, stdin);

        char * myArgs[MAX_ARGS];
        parseInput(myArgs,line, MAX_ARGS);

        int res = checkBuiltIn(myArgs[0]);
        if(res > 0){
            switch (res)
            {
            case 1:
                alive = 0;
                break;
            case 2:
                /* code */
                printf("Built in command cd\n");
                break;
            case 3:
                /* code */
                printf("Built in command path\n");
                break;
            
            default:
                break;
            }
        }else{
            // Process creation for the command
            pid_t child_pid;
            child_pid = fork();

            if(child_pid == -1){
                perror("fork() failed\n");
                exit(EXIT_FAILURE);
            }else if(child_pid == 0){
                // child
                // search in paths
                char *path_token = strtok(path_copy, ":");
                while (path_token != NULL) {
                    char full_path[strlen(path_token) + strlen(myArgs[0]) + 2];
                    sprintf(full_path, "%s/%s", path_token, myArgs[0]);
                    if(access(full_path,X_OK) == 0){
                        execv(full_path, myArgs);
                    }
                    // If execv succeeds, the program will not reach here
                    path_token = strtok(NULL, ":");
                }

                perror("The executable does not exist in the given paths");
                exit(EXIT_FAILURE);
            }else{
                // parent
                int status;
                pid_t terminated_child_pid = waitpid(child_pid,&status,0);
                if(terminated_child_pid == -1){
                    perror("waitpid failed");
                    exit(EXIT_FAILURE);
                }
                //if (WIFEXITED(status)) {
                    //printf("Parent: Child process %d has terminated with status %d\n",
                    //terminated_child_pid, WEXITSTATUS(status));
                //} 
            }
        }

    }
    free(line);
    free(new_path);
    free(path_copy);
    return 0;
}