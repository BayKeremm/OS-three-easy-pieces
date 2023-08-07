#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int zipFunc(FILE * input){
    size_t n = 1;
    int bytesRead;

    char * buffer = (char *) malloc(n * sizeof(char));
    if (buffer == NULL){
        printf("Unable to allocate buffer\n");
        return 1;
    }
    while ((bytesRead = getline(&buffer,&n,input)) != -1){
        char counter=1;
        char * ptr1 = buffer;
        char * ptr2 = ptr1+1;
        char * end = buffer + bytesRead;
        while(ptr1 < end){
            if(ptr2 < end &&*ptr1 == *ptr2){
                counter++;
            }else{
                char num[5];
                snprintf(num, sizeof(num), "%d",counter);
                char s[6];
                snprintf(s, sizeof(s), "%s%c",num,*ptr1);
                fwrite(s,sizeof(s)- 1,1,stdout);
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

    for(int i = 1 ; i < argc ; i++){
        FILE * file = fopen(argv[i],"r");
        if(file == NULL){
            printf("wzip: cannot open file\n");
            exit(1);
        }
        char res = zipFunc(file);
        fclose(file);
        if(res){
            exit(1);
        }
    }
    //FILE * file = fopen("text.txt","r");
    //if(file == NULL){
        //printf("wzip: cannot open file\n");
        //exit(1);
    //}
    //char res = zipFunc(file);
    //fclose(file);
    //if(res){
        //exit(1);
    //}
    return 1;
}