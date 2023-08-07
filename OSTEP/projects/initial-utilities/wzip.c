#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int zipFunc(FILE * input){
    char * buffer;
    size_t n = 100;

    buffer = (char *) malloc(n * sizeof(char));
    if (buffer == NULL){
        printf("Unable to allocate buffer\n");
        return 1;
    }
    while (getline(&buffer,&n,input) > -1){
        char counter=1;
        char * ptr1 = buffer;
        char * ptr2 = ptr1+1;
        char * end = buffer + sizeof(buffer);
        while(ptr1 <= end){
            if(ptr2 <= end &&*ptr1 == *ptr2){
                counter++;
            }else{
                char num[4];
                sprintf(num,"%d",counter);
                char s[5];
                sprintf(s,"%s%c",num,*ptr1);
                fwrite(s,5,1,stdout);
                counter = 1;
            }
            ptr1++; 
            ptr2++; 
        }
    }
    free(buffer);

    return 0;
}

int main(int argc, char * argv[]){
    if(argc < 2){
        perror("Please check the arguements\n");
        exit(1);
    }
    char * fileName = argv[1];
    FILE * file = fopen(fileName,"r");
    if(file == NULL){
        printf("wzip: cannot open file\n");
        exit(1);
    }
    zipFunc(file);
    fclose(file);
    return 1;
}