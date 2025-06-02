#ifndef LISTFUNCTIONS_H
#define LISTFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>

typedef struct wList {
    char *word;
    int wordLength;
    int uniqLetters;
    int numOfTimes;
    int insertionMode;
    char date[11];
    char time[6];
    struct wList *next;
    struct wList *previous;
} wordList;

#endif
