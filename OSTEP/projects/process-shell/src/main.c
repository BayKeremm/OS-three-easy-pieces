#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/wait.h>


int main(int argc, char * argv[])
{
    char * line;
    size_t n = 100;

    line = (char *) malloc(n * sizeof(char));

    if (line == NULL){
        printf("Unable to allocate buffer\n");
        return 1;
    }
    for(;;){
        printf("wish> ");

        if(getline(&line,&n,stdin)>-1 ){
            printf("%s",line);
        }

        pid_t child_pid;
        child_pid = fork();

        if(child_pid == -1){
            perror("fork() failed\n");
            exit(EXIT_FAILURE);
        }else if(child_pid == 0){
            // child
            printf("Halo from child");
            exit(EXIT_SUCCESS);
        }else{
            // parent
            int status;
            pid_t terminated_child_pid = waitpid(child_pid,&status,0);
            if(terminated_child_pid == -1){
                perror("waitpid failed");
                exit(EXIT_FAILURE);
            }
            if (WIFEXITED(status)) {
            //printf("Parent: Child process %d has terminated with status %d\n",
                   //terminated_child_pid, WEXITSTATUS(status));
            } 
        }
    }
    free(line);
    return 0;
}