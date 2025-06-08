#ifndef LISTFUNCTIONS_H
#define LISTFUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include "commonFunc.h"

typedef struct wList {
    char *word;
    int wordLength;
    int uniqLetters;
    int numOfTimes;
    int insertionMode; // 0 = from file, 1 = from key
    char date[11];
    char time[6];
    struct wList *next;
    struct wList *previous;
} wordList;

void takeInput(char args[], char command[], wordList **head, wordList **tail);
void printForward(wordList *head, char word[]);
void printReverse(wordList *tail, char word[]);

#endif
