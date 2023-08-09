#include "stdio.h"
#include "stdlib.h"
#include "string.h"

int zipFunc(FILE * input){
    size_t n = 100;
    int bytesRead;

    char * buffer = (char *) malloc(n * sizeof(char));
    if (buffer == NULL){
        printf("Unable to allocate buffer\n");
        return 1;
    }
    while ((bytesRead = getline(&buffer,&n,input)) != -1){
        int counter=1;
        char * ptr1 = buffer;
        char * ptr2 = ptr1+1;
        char * end = buffer + bytesRead;
        while(ptr1 < end){
            if(strncmp(ptr1,ptr2,1)==0){
                counter++;
            }else{
                fwrite(&counter,4,1,stdout);
                fwrite(ptr1,1,1,stdout);
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
        printf("wzip: file1 [file2 ...]\n");
        exit(1);
    }
    if(argc > 2){
        // Combine files
        FILE * combined = fopen("combined.x","w");
        if(combined == NULL){
            printf("wzip: cannot create file\n");
            exit(0);
        }
        for(int i = 1 ; i < argc ; i++){
            FILE * file = fopen(argv[i],"r");
            if(file == NULL){
                printf("wzip: cannot open file\n");
                exit(0);
            }
            char ch;
            while((ch = fgetc(file)) != EOF){
                fputc(ch,combined);
            }
            fclose(file);
        }
        fclose(combined);
        FILE * input = fopen("combined.x","r");
        if(input == NULL){
            printf("wzip: cannot open file\n");
            exit(0);
        }
        char res = zipFunc(input);
        fclose(input);
        if(res){
            exit(1);
        }
        if(remove("combined.x")){
            printf("Combined file not removed successfully\n");
            exit(1);
        }

    }else{
        FILE * input = fopen(argv[1],"r");
        if(input == NULL){
            printf("wzip: cannot open file\n");
            exit(0);
        }
        char res = zipFunc(input);
        fclose(input);
        if(res){
            exit(1);
        }
    }
    //for(int i = 1 ; i < argc ; i++){
        //FILE * file = fopen(argv[i],"r");
        //if(file == NULL){
            //printf("wzip: cannot open file\n");
            //exit(0);
        //}
        //char res = zipFunc(file);
        //fclose(file);
        //if(res){
            //exit(1);
        //}
    //}
    return 0;
}