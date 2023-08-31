#include "input_handler.h"
int getUserInput(char ** lineptr, size_t * n, FILE * stream){
    if(getline(lineptr,n,stream)==-1 ){
        perror("nothing more to read");
        exit(EXIT_SUCCESS);
    }
    return 0;
}