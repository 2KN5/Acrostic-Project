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
    double difficulty;
    char date[11];
    char time[6];
    struct wList *next;
    struct wList *previous;
} wordList;

// Input handling: from keyboard or .txt file.
void takeInput(wordList **head, wordList **tail, char args[], char command[]);

// Print words.
void printForward(wordList *head, char args[]);
void printReverse(wordList *tail, char args[]);

// Find and display words.
void findForward(wordList *head, char args[]);
void findReverse(wordList *tail, char args[]);

// Extract and delete valid words from a string.
void extractWords_DELETION(wordList **head, wordList **tail, char str[]);

#endif
