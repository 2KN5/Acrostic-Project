#include <stdio.h>
#include <stdlib.h>
#include "commonFunc.h"

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
        printf(">");

        // Read the line dynamically.
        char *action = readLine();
        if(!action || (strcmp(action, "exit") == 0)) return 0;

        // Handle the other commands in commandHandler, to keep main clean.
        //handleCommands();
        //free(action);
    }
    return 0;
}