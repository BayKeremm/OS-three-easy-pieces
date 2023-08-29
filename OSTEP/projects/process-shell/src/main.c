#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <string.h>
#include <sys/wait.h>

#define MAX_ARGS 10


int main(int argc, char * argv[])
{
    
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
    for(;;){
        printf("wish> ");

        if(getline(&line,&n,stdin)==-1 ){
            perror("nothing more to read");
            exit(EXIT_SUCCESS);
        }

        line[strcspn(line,"\n")] = ' ';
        char * myArgs[MAX_ARGS];
        char * token = strtok(line, " ");
        int argIndex = 0;

        while(token != NULL && argIndex < MAX_ARGS -1){
            myArgs[argIndex] = token;
            argIndex++;
            token = strtok(NULL," ");
        }

        myArgs[argIndex] = NULL;

        if(strcmp(myArgs[0],"exit") == 0){
            goto end;
        }

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
    end:
    free(line);
    free(new_path);
    free(path_copy);
    return 0;
}