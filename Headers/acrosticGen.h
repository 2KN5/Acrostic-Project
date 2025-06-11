#ifndef ACROSTICGEN_H
#define ACROSTICGEN_H

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "commonFunc.h"
#include "listFunctions.h"

void createAcr(wordList *head, wordList *tail, char args[], char ***latestAcr, int *latestAcrCount);
void saveAcr(char fileName[], char ***latestAcr, int *latestAcrCount);

#endif
