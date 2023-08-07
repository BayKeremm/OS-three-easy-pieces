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
        char * ptr2 = ptr1++;
        char * end = buffer + sizeof(buffer);
        while(ptr2 <= end){
            if(*ptr1 == *ptr2){
                counter++;
            }else{
                char num[4];
                sprintf(num,"%d",counter);
                char s[5];
                char * prev = ptr1-1;
                sprintf(s,"%s%c",num,*prev);
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
        printf("wcat: cannot open file\n");
        exit(1);
    }
    zipFunc(file);
    return 1;
}