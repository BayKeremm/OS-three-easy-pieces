#include <stdio.h>
#include <stdlib.h>
int catFunc(char * fileName){
    FILE * file = fopen(fileName,"r");
    if(file == NULL){
        printf("wcat: cannot open file\n");
        return 1;
    }
    char buffer[100];
    while (fgets(buffer, sizeof(buffer), file) != NULL) {
        printf("%s", buffer);
    }
    fclose(file);
    return 0;
}
int main(int argc,char* argv[]){

    if (argc == 1){
        printf("Error, pass file name(s)\n");
        return 0;
    }

    for(int i = argc -1; i > 0 ; i--){
        if(catFunc(argv[i])){
            exit(1);
        }
        printf("\n");
    }
    return 0;
}