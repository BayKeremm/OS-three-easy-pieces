#include <stdio.h>
#include <stdlib.h>
int grepFunc(char * fileName){
    FILE * file = fopen(fileName,"r");
    if(file == NULL){
        printf("wgrep: cannot open file\n");
        return 1;
    }
    // TODO: grep utility
    
    fclose(file);
    return 0;
}
int main(int argc, char * argv[]){
    if (argc < 3){
        printf("Error, usage is wrong\n");
        return 0;
    }
    for(int i = argc -1; i > 0 ; i--){
    }
    return 0;
}