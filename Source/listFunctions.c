#include "listFunctions.h"

void getTxtName(char str[], char *txtName){
    int count = 0;
    while(str[count] != ' ' && str[count] != '\0'){
        txtName[count] = str[count];
        ++count;
    }
    txtName[count] = '\0';
    strcat(txtName, ".txt");
}

int countUniqLetters(char word[]){
    char letters[26] = {0};
    for(int i = 0; i < strlen(word); ++i){
        ++letters[word[i] - 'A'];
    }
    int count = 0;
    for(int i = 0; i < 26; ++i){
        if(letters[i]) ++count;
    }
    return count;
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
    newNode->uniqLetters = countUniqLetters(inputWord);
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
        printf("\n%s - accepted and added to the list.\n", inputWord);
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
    printf("\n%s - accepted and added to the list.\n", inputWord);
}

int countWords(wordList *ptr, int ht){
    if(ht == 0){
        int words = 0;
        while(ptr){
            ++words;
            ptr = ptr->next;
        }
        return words;
    } else {
        int words = 0;
        while(ptr){
            ++words;
            ptr = ptr->previous;
        }
        return words;
    }
}

void printForward(wordList *head, char args[]){
    // Get number of words in the wlist.
    int numOfWords = countWords(head, 0);

    // Find the first number in the string.
    int count = 0;
    char *numChar = malloc(strlen(args) + 1);
    while(isdigit(args[count])){
        numChar[count] = args[count];
        ++count;
    }
    numChar[count] = '\0';

    // Check if the number is valid.
    if(strcmp(args, numChar) != 0){
        printf("\nInvalid Input!\n\n");
        free(numChar);
        return;
    }

    // If it's valid print the words.
    printf("\n------------------------------------------------------\n\n");
    int c = 0;
    int num = atoi(numChar), finalNum = (num > numOfWords ? numOfWords : num);
    while(head && c < finalNum){
        printf("Word %d: %s\n", c + 1, head->word);
        head = head->next;
        ++c;
    }
    if(c == 0) printf("No matches found.\n");
    printf("\n------------------------------------------------------\n\n");
    free(numChar);
}

void printReverse(wordList *tail, char args[]){
    // Get number of words in the wlist.
    int numOfWords = countWords(tail, 1);

    // Find the first number in the string.
    int count = 0;
    char *numChar = malloc(strlen(args) + 1);
    while(isdigit(args[count])){
        numChar[count] = args[count];
        ++count;
    }
    numChar[count] = '\0';

    // Check if the number is valid.
    if(strcmp(args, numChar) != 0){
        printf("\nInvalid Input!\n\n");
        free(numChar);
        return;
    }

    // If it's valid print the words.
    printf("\n------------------------------------------------------\n\n");
    int c = 0;
    int num = atoi(numChar), finalNum = (num > numOfWords ? numOfWords : num);
    while(tail && c < finalNum){
        printf("Word %d: %s\n", c + 1, tail->word);
        tail = tail->previous;
        ++c;
    }
    if(c == 0) printf("No matches found.\n");
    printf("\n------------------------------------------------------\n\n");
    free(numChar);
}

void findForward(wordList *head, char args[]){
    // Get the 2 first strings.
    int length = strlen(args);
    char *word1 = malloc(length + 1), *word2 = malloc(length + 1);
    char *token = strtok(args, " \n");
    if(token == NULL){
        printf("\nInvalid Input!\n\n");
        free(word1); free(word2);
        return;
    }
    strcpy(word1, token);
    token = strtok(NULL, " \n");
    if(token == NULL){
        printf("\nInvalid Input!\n\n");
        free(word1); free(word2);
        return;
    }
    strcpy(word2, token);

    // Check if the argument ends there.
    token = strtok(NULL, " \n");
    if(token == NULL){
        for(int i = 0; word2[i] != '\0'; ++i){
            if(!isdigit(word2[i])){
                printf("\nInvalid Input!\n\n");
                free(word1); free(word2);
                return;
            }
        }

        // Print the words found.
        printf("\n------------------------------------------------------\n\n");
        int i = 0, count = atoi(word2);
        while(head && i < count){
            if(strncmp(word1, head->word, strlen(word1)) == 0){
                printf("Word %d: %s\n", i + 1, head->word);
                ++i;
            }
            head = head->next;
        }
        if(i == 0) printf("No matches found.\n");
        printf("\n------------------------------------------------------\n\n");
    } else {
        printf("\nInvalid Input!\n\n");
        free(word1); free(word2);
        return;
    }
    free(word1); free(word2);
}

void findReverse(wordList *tail, char args[]){
    // Get the 2 first strings.
    int length = strlen(args);
    char *word1 = malloc(length + 1), *word2 = malloc(length + 1);
    char *token = strtok(args, " \n");
    if(token == NULL){
        printf("\nInvalid Input!\n\n");
        free(word1); free(word2);
        return;
    }
    strcpy(word1, token);
    token = strtok(NULL, " \n");
    if(token == NULL){
        printf("\nInvalid Input!\n\n");
        free(word1); free(word2);
        return;
    }
    strcpy(word2, token);

    // Check if the argument ends there.
    token = strtok(NULL, " \n");
    if(token == NULL){
        for(int i = 0; word2[i] != '\0'; ++i){
            if(!isdigit(word2[i])){
                printf("\nInvalid Input!\n\n");
                free(word1); free(word2);
                return;
            }
        }
        
        // Print the words found.
        printf("\n------------------------------------------------------\n\n");
        int i = 0, count = atoi(word2);
        while(tail && i < count){
            if(strncmp(word1, tail->word, strlen(word1)) == 0){
                printf("Word %d: %s\n", i + 1, tail->word);
                ++i;
            }
            tail = tail->previous;
        }
        if(i == 0) printf("No matches found.\n");
        printf("\n------------------------------------------------------\n\n");
    } else {
        printf("\nInvalid Input!\n\n");
        free(word1); free(word2);
        return;
    }
    free(word1); free(word2);
}

void extractWords(char str[], wordList **head, wordList **tail, int mode){
    // Convert to upper.
    stringToUpper(str);

    // Break the string into a series of tokens.
    char *token = strtok(str, " \n");
    
    while(token != NULL){
        // Remove characters from beginning and end.
        int tokenStart = 0, tokenEnd = strlen(token) - 1;
        while(!isalpha(token[tokenStart]) && tokenStart <= tokenEnd) ++tokenStart;
        while(!isalpha(token[tokenEnd]) && tokenEnd >= tokenStart) --tokenEnd;

        // We have the word, now check if it's valid.
        int count = 0, f = 1, length = tokenEnd - tokenStart + 2;
        char *word = malloc(length);
        for(int i = tokenStart; i <= tokenEnd; ++i){
            if(!isalpha(token[i])){
                f = 0;
                break;
            }
            word[count] = token[i];
            ++count;
        }

        // If word is invalid, reject.
        if(!f){
            printf("\n%s - is not valid and was rejected.\n", token);
            token = strtok(NULL, " \n");
            continue;
        }      

        // If it's valid, insert the word into the list.
        word[count] = '\0';
        if(count >= 1) insertWord(head, tail, word, mode);
        free(word);
        token = strtok(NULL, " \n");
    }
}

void takeInput(char args[], char command[], wordList **head, wordList **tail){
    // Check if it's input from the keyboard or a .txt file.
    if(strcmp(command, "INSERT") == 0){      
        // Put words into the list.  
        extractWords(args, head, tail, 1);
        printf("\n");
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
        printf("\nFull Path: %s\n", path);
        
        char *fileName = path;
        FILE *file = fopen(fileName, "r");
        if(!file){
            printf("\n-Failed to open: %s\n\n", txtName);
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

        printf("\n-Succeded in opening: %s\n\n", txtName);
        free(contents);
        free(txtName);
        fclose(file);
    }
}
