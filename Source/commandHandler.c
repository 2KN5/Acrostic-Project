#include "commandHandler.h"

int getCommand(char str[], char command[]){
    char temp[10];
    int count = 0;
    while(count < 9 && str[count] != ':' && str[count] != '\0'){
        temp[count] = str[count];
        ++count;
    }
    // Check if command is at least 4 characters(load), and ends with a colin.
    if(str[count] != ':' || count < 4) return 0;

    // If the above conditions are true, we have the command(We still need to check if it's valid).
    temp[count] = '\0';
    strcpy(command, temp);
    return 1;
}

int checkValidCommand(char command[]){
    // Convert to upper and check if it's one of the valid words.
    char *validCommands[] = {"INSERT", "DELETE", "SHOWFWD", "SHOWREV", "FINDFWD", "FINDREV", "CREATE", "LOAD", "SAVE"};
    int elements = sizeof(validCommands) / sizeof(validCommands[0]);

    for(int i = 0; i < elements; ++i){
        if(strcmp(command, validCommands[i]) == 0) return 1;
    }
    return 0;
}

void handleCommand(char string[], wordList **head, wordList **tail){
    char command[10];
    if(!getCommand(string, command) || !checkValidCommand(command)){
        printf("\nInvalid command!\n\n"); 
        pause();
        return;
    }
    if(strcmp(command, "INSERT") == 0 || strcmp(command, "LOAD") == 0){
        takeInput(string, command, head, tail);
    } else if(strcmp(command, "DELETE") == 0){
        printf("Deleting element...\n");
    } else if(strcmp(command, "SHOWFWD") == 0 || strcmp(command, "SHOWREV") == 0){
        //int num = extractNum(string);
        if(strstr(command, "FWD")){
            //printForward(*head, num);
        } else {
            //printReverse(*tail, num);
        }
    } else if(strcmp(command, "FINDFWD") == 0 || strcmp(command, "FINDREV") == 0){
        if(strstr(command, "FWD")){
            printf("FORWARDS\n");
        } else {
            printf("REVERSE\n");
        }
    } else if(strcmp(command, "CREATE") == 0){
        printf("Creating element...\n");
    } else {
        printf("Saving contents...\n");
    }
    pause();
}
