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
    while(1){

        // Setting up environment.
        clearScreen();
        printf("\n>");

        // Read the line dynamically.
        char *action = readLine();
        stringToUpper(action);
        if(!action || (strcmp(action, "EXIT") == 0)) return 0;

        // Handle the other commands in commandHandler, to keep main clean.
        handleCommand(action);
        free(action);
    }
    return 0;
}