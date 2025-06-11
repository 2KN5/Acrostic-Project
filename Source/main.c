#include <stdio.h>
#include <stdlib.h>
#include "commandHandler.h"

/*

Konstantinos Tampouris
AM: 2022202400200
dit24200@uop.gr

Orfeas Vasilis Mermigas
AM: 2022202400122
dit24122@uop.gr

*/

int main(void){

    // Seed for rand.
    srand(time(NULL));

    // Head and tail.
    wordList *head = NULL, *tail = NULL;

    // For saving the latest acrostic.
    int latestAcrCount = 0;
    char **latestAcrostic = NULL;

    // Let's begin.
    while(1){

        // Setting up environment.
        clearScreen();
        printf("\n>");

        // Read the line dynamically.
        char *action = readLine();

        // Convert to upper and check the kind of action.
        stringToUpper(action);
        if(!action || (strcmp(action, "EXIT") == 0)){
            free(action);
            return 0;
        }

        // Handle the other commands in commandHandler, to keep main clean.
        handleCommand(&head, &tail, action, &latestAcrostic, &latestAcrCount);
        free(action);
    }

    // Free the list.
    wordList *curr = head;
    while(curr){
        wordList *next = curr->next;
        free(curr->word); // We used malloc here too -> OM
        free(curr);
        curr = next;
    }
    
    // Free acrostic saved.
    if(latestAcrostic){
        for(int i = 0; i < latestAcrCount; ++i){
            free(latestAcrostic[i]);
        }
        free(latestAcrostic);
    }

    // End.
    return 0;
}