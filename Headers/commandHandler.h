#ifndef COMMANDHANDLER_H
#define COMMANDHANDLER_H

#include <stdio.h>
#include <stdlib.h>
#include "commonFunc.h"
#include "listFunctions.h"
#include "acrosticGen.h"

void handleCommand(wordList **head, wordList **tail, char string[], char ***latestAcr, int *latestAcrCount);

#endif 
