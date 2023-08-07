#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int grepFunc(FILE * file, char * toSearch){
    char * linep;
    size_t n = 100;

    linep = (char *) malloc(n * sizeof(char));
    if (linep == NULL){
        printf("Unable to allocate buffer\n");
        return 1;
    }
    while (getline(&linep,&n,file) > -1){
        if(strstr(linep,toSearch) != NULL){
            printf("%s",linep);
        }
    }
    free(linep);
    return 0;
}
int main(int argc, char * argv[]){
    if (argc < 2){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    char * s = argv[1];
    if (argc == 2){
        char res = grepFunc(stdin,s);
        if(res){
            exit(1);
        }
    }else{
        for(int i = argc - 1 ; i > 1 ; i--){
            FILE * file = fopen(argv[i],"r");
            if(file == NULL){
                printf("wgrep: cannot open file\n");
                exit(1);
            }
            char res = grepFunc(file,s);
            fclose(file);
            if(res){
                exit(1);
            }
        }

    }
    return 0;
}