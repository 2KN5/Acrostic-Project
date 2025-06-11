#include "acrosticGen.h"

int getNumberOfWords(wordList *head){
    int count = 0;
    while(head){
        ++count;
        head = head->next;
    }
    return count;
}

int compare_DIFFICULTY(const void *a, const void *b){
    wordList *w1 = *(wordList **)a;
    wordList *w2 = *(wordList **)b;

    // Compare by difficulty.
    if(w1->difficulty > w2->difficulty) return 1;
    if(w1->difficulty < w2->difficulty) return -1;
    return 0;
}

void calcDiff(wordList **arr){
    wordList *temp = *arr;
    while(temp){
        // Get scores for each component.
        double lengthScore = (temp->wordLength <= 1 ? 0.0 : fmin(0.5 * temp->wordLength, 5.0));
        double uniqScore = (temp->uniqLetters <= 1 ? 0.0 : fmin(0.3 * temp->uniqLetters, 3.0));
        double freqScore = 2.0 - fmin(0.13 * temp->numOfTimes, 2.0); // After numOfTimes hits 15+, the frequency score becomes 0.
        
        // Calculate final score.
        double diff = fmax(1.0, lengthScore + uniqScore + freqScore);
        temp->difficulty = round(diff * 10.0) / 10;

        // If it's 9.9, make it a 10.
        if(temp->difficulty == 9.9) temp->difficulty = 10.0; 
        temp = temp->next;
    }
}

int parseStrings(char **w1, char **w2, char args[]){
    int length = strlen(args);
    *w1 = malloc(length + 1), *w2 = malloc(length + 1);
    char *token = strtok(args, " \n");
    if(token == NULL){
        free(*w1); free(*w2);
        return 0;
    }
    strcpy(*w1, token);
    token = strtok(NULL, " \n");
    if(token == NULL){
        free(*w1); free(*w2);
        return 0;
    }
    strcpy(*w2, token);

    // Check if the argument ends there.
    token = strtok(NULL, " \n");
    if(token == NULL && (strcmp(*w2, "EASY") != 0 && strcmp(*w2, "HARD") != 0)){
        free(*w1); free(*w2);
        return 0;
    }
    return 1;
}

void saveAcr(char fileName[], char ***latestAcr, int *latestAcrCount){
    if(!(*latestAcr)){
        printf("\nNo previous acrostic to save!\n\n");
        return;
    }
    char path[512] = "C:/Users/Kon Tampouris/Desktop/Project 2/Acrostic/Save/", *txtName = (char*)malloc(strlen(fileName) + 5);
    if(!txtName){
        printf("Memory allocation failed for \"txtName\"!");
        return;
    }
    getTxtName(fileName, txtName);
    strcat(path, txtName);
    FILE *file = fopen(path, "w");
    if(!file){
        printf("\n-Failed to create: %s\n\n", txtName);
        return;
    }
    for(int i = 0; i < *latestAcrCount; ++i){
        fprintf(file, "%s\n", (*latestAcr)[i]);
    }
    printf("\nSuccessfully saved the most recent acrostic!\n\n");
    fclose(file);
}

void createAcr(wordList *head, wordList *tail, char args[], char ***latestAcr, int *latestAcrCount){

    // Get the 2 first strings.
    int length = strlen(args);
    char *word1 = NULL, *word2 = NULL;
    if(!parseStrings(&word1, &word2, args)){
        printf("\nInvalid Input!\n\n");
        // Already freed in parseStrings.
        return;
    }

    // Get number of words and check if list is empty.
    int numOfWords = getNumberOfWords(head);
    if(numOfWords == 0){
        printf("\nThe list is empty! Insert / Load some words first.\n\n");
        free(word1); free(word2);
        return;
    }

    // Get max length out of all words in the list.
    int maxLength = 0;
    wordList *temp = head;
    while(temp){
        maxLength = fmax(maxLength, temp->wordLength);
        temp = temp->next;
    }

    // Initialize the string (We need this to save the output);
    int acrCount = 0;
    char **tempAcr = (char**)malloc(sizeof(char*) * strlen(word1));
    for(int i = 0; i < strlen(word1); ++i){
        tempAcr[i] = (char*)malloc(sizeof(char) * (maxLength + 1));
    }
    
    // Loop through the elements of "word1".
    for(int i = 0; i < strlen(word1); ++i){

        // Count number of words with that letter.
        int wordsWithLetter = 0, maxLength = -1;
        wordList *temp = head;
        while(temp){
            if(word1[i] == temp->word[0]){
                ++wordsWithLetter;
            }
            temp = temp->next;
        }
        if(wordsWithLetter == 0){
            printf("\nNo word found starting with '%c' in the list for difficulty level '%s'. Cannot create acrostic.\n\n", word1[i], word2);

            // Free word1, word2 and tempAcr.
            free(word1); free(word2);
            for(int i = 0; i < strlen(word1); ++i){
                free(tempAcr[i]);
            }
            free(tempAcr);

            return;
        }

        // Save them in an array.
        // So arr[0] has the contents of the first node, arr[1] the contents of the second note, and so on.
        wordList *arr[wordsWithLetter];
        int count = 0;
        temp = head;
        while(temp){
            if(word1[i] == temp->word[0]){
                arr[count] = temp;
                ++count;
            }
            temp = temp->next;
        }

        // Calculate the difficulty of each word.
        calcDiff(arr);

        // Sort the array by difficulty.
        qsort(arr, wordsWithLetter, sizeof(wordList *), compare_DIFFICULTY);

        // Find a random word depending on the difficulty and store in array "acrostic".
        int middle = wordsWithLetter / 2, randomIndex, range;
        if(strcmp(word2, "EASY") == 0){
            range = fmax(middle, 1);
            randomIndex = rand() % range;
        } else {
            range = fmax(wordsWithLetter - middle, 1);
            randomIndex = rand() % range + middle;
        }
        strcpy(tempAcr[acrCount++], arr[randomIndex]->word);
    }

    // Create the last string array, where we are going to store the final acrostic.
    int elemCount = 0;
    char **acrostic = (char**)malloc(sizeof(char*) * (acrCount * 2 + 2));
    for(int i = 0; i < (acrCount * 2 + 2); ++i){
        acrostic[i] = (char*)malloc(sizeof(char) * (maxLength + 1));
    }
    
    // Store the acrostic the way the project wants us to.
    for(int i = 0; i < acrCount; ++i){
        int count = 0;
        char str[maxLength];
        strcpy(str, tempAcr[i]);
        for(int j = 1; j < strlen(str); ++j){
            if(rand() % 3 == 0){
                str[j] = '_';
                ++count;
            }
        }
        if(!count && strlen(str) > 1){
            int randomIndex = rand() % (strlen(str) - 1) + 1;
            str[randomIndex] = '_';
        }
        strcpy(acrostic[elemCount++], str);
    }
    strcpy(acrostic[elemCount++], " ");
    for(int i = 0; i < acrCount; ++i){
        strcpy(acrostic[elemCount++], tempAcr[i]);
    }

    // Print the acrostic.
    printf("\n------------------------------------------------------\n\n");
    for(int i = 0; i < elemCount; ++i){
        printf("%s\n", acrostic[i]);
    }
    printf("\n------------------------------------------------------\n\n");

    // Free the old acrostic if a new one is generated.
    if((*latestAcr)){
        for(int i = 0; i < (*latestAcrCount); ++i){
            free((*latestAcr)[i]);
        }
        free(*latestAcr);
    }
    *latestAcr = acrostic;
    *latestAcrCount = elemCount;

    free(word1); free(word2);
}