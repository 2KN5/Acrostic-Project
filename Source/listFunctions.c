#include "listFunctions.h"

// Find the colon, and return a pointer right after it. 
char *getColon(char str[]){
    char *c = strchr(str, ':');
    return (c == NULL ? NULL : c + 1);
}

char getTxtName(char str[], char *txtName){
    int count = 0;
    while(str[count] != ' ' && str[count] != '\0'){
        txtName[count] = str[count];
        ++count;
    }
    txtName[count] = '\0';
    strcat(txtName, ".txt");
}

void extractWords(char str[]){
    
}

void takeInput(char str[], char command[]){
    // Get the string after the colon.
    char *args = getColon(str);
    if(!args){
        printf("Failed!\n");
        return;
    }
    while(*args == ' ') ++args;

    // Check if it's input from the keyboard or a .txt file.
    if(strcmp(command, "INSERT") == 0){        
        printf("\nRest of the string: %s\n\n", args);
    } else {
        printf("\nLoading string from file...\n");
        
        // Get the full path of the .txt file.
        char path[512] = "C:/Users/Kon Tampouris/Desktop/Project 2/Acrostic/example_txts/", *txtName = (char*)malloc(strlen(args) + 1);
        if(!txtName){
            printf("Memory allocation failed for \"txtName\"!");
            return;
        }
        getTxtName(args, txtName);
        strcat(path, txtName);

        printf("\nFull Path: %s\n\n", path);

        char *fileName = path;
        FILE *file = fopen(fileName, "r");
        if(!file){
            printf("Failed to open: %s\n\n", txtName);
            return;
        }
        printf("Succeded in opening: %s\n\n", txtName);
        fclose(file);
    }
    //extractWords(args);
}