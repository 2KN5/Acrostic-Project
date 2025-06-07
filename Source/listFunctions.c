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

void insertWord(wordList **head, wordList **tail, char inputWord[], int mode){
    // Check if the word already exists.
    wordList *curr = *head;
    while(curr){
        if(strcmp(curr->word, inputWord) == 0){
            ++(curr->numOfTimes);
            return;
        }
        curr = curr->next;
    }

    // Allocate the new node.
    wordList *newNode = malloc(sizeof(wordList));
    newNode->word = strdup(inputWord);
    newNode->wordLength = strlen(inputWord);
    //newNode->uniqLetters = countUniqLetters(inputWord);
    newNode->numOfTimes = 1;
    newNode->insertionMode = mode;

    // Get date and time.
    time_t rawTime = time(NULL);
    struct tm *info = localtime(&rawTime);
    strftime(newNode->date, sizeof(newNode->date), "%d-%m-%Y", info);
    strftime(newNode->time, sizeof(newNode->time), "%H:%M", info);

    newNode->next = NULL;
    newNode->previous = NULL;
    
    // Check if list is empty.
    if(*head == NULL){
        *head = *tail = newNode;
        return;
    }

    // Find where it belongs alphabetically.
    curr = *head;
    while(curr && strcmp(inputWord, curr->word) > 0){
        curr = curr->next;
    }
    
    // Insert the word.
    if(curr == NULL){
        // It's greater than all the words, place at the end.
        (*tail)->next = newNode;
        newNode->previous = (*tail);
        (*tail) = newNode;
    } else if(curr == *head){
        // It's less than all the words, place at the beginning.
        (*head)->previous = newNode;
        newNode->next = (*head);
        (*head) = newNode;
    } else {
        // It's in the middle, place accordingly
        newNode->next = curr;
        newNode->previous = curr->previous;
        curr->previous->next = newNode;
        curr->previous = newNode;
    }
}

void extractWords(char str[], wordList **head, wordList **tail, int mode){
    stringToUpper(str);
    for(int i = 0; str[i] != '\0'; ++i){
        if(!isalpha(str[i])) str[i] = ' ';
    }
    while(*str == ' ') ++str;
    long length = strlen(str);
    char *word = malloc(length + 1);
    int count = 0;
    for(int i = 0; str[i] != '\0'; ++i){
        if(isalpha(str[i])){
            word[count] = str[i];
            ++count;
        } else if(count > 1){
            word[count] = '\0';
            insertWord(head, tail, word, mode);
            count = 0;
        } else {
            count = 0;
        }
    }
    if(count >= 1){
        word[count] = '\0';
        insertWord(head, tail, word, mode);
        count = 0;
    }
    free(word);
    printf("\n");
}

void printList(wordList *head){
    int count = 1;
    while(head){
        printf("Word %d: %s\n", count, head->word);
        head = head->next;
        ++count;
    }
}

void takeInput(char str[], char command[], wordList **head, wordList **tail){
    // Get the string after the colon.
    char *args = getColon(str);
    if(!args){
        printf("Failed!\n");
        return;
    }
    while(*args == ' ') ++args;
    
    // Check if it's input from the keyboard or a .txt file.
    if(strcmp(command, "INSERT") == 0){      
        // Put words into the list.  
        extractWords(args, head, tail, 1);
        printf("\n\n");
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
        
        // Print Path.
        printf("\nFull Path: %s\n\n", path);
        
        char *fileName = path;
        FILE *file = fopen(fileName, "r");
        if(!file){
            printf("Failed to open: %s\n\n", txtName);
            return;
        }

        // Get the file size and dynamically allocate memory for the string.
        fseek(file, 0, SEEK_END);
        long fileSize = ftell(file);
        rewind(file);
        char *contents = malloc(fileSize + 1);

        // Store the contents of the .txt file in a string, and extract the words.
        fread(contents, sizeof(char), fileSize, file);
        contents[fileSize] = '\0';

        // Put words into the list.  
        extractWords(contents, head, tail, 0);

        printf("\n\nSucceded in opening: %s\n\n", txtName);
        free(contents);
        free(txtName);
        fclose(file);
    }
    printList(*head);
}