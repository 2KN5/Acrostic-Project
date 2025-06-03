#ifndef COMMONFUNC_H
#define COMMONFUNC_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include <time.h>

static inline void clearScreen(){
    #ifdef _WIN32
        system("cls");
    #else
        system("clear");
    #endif
}

static inline void pause(){
    printf("Press ENTER to continue...");
    getchar();
}

static inline void stringToUpper(char str[]){
    for(int i = 0; str[i] != '\0'; ++i){
        str[i] = toupper(str[i]);
    }
}

static inline char *readLine(){
    int buffer = 16, length = 0;
    char *string = (char*)malloc(buffer);
    
    // Check if memory allocation failed.
    if(!string){
        printf("Memory allocation failed!\n");
        return NULL;
    }

    // Resize the string if necessary.
    int c;
    while((c = getchar()) != '\n' && c != EOF){
        string[length] = c;
        ++length;
        if(length >= buffer){
            buffer *= 2;
            char *temp = realloc(string, buffer);
            // Check if memory re-allocation failed.
            if(!temp){
                printf("Memory re-allocation failed!");
                return NULL;
            }
            string = temp;
        }
    }
    string[length] = '\0';
    return string;
}

#endif 
