#include "Trie.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

char* appendChar(char *str, char c) {
        int len = 0;
        while(str[len] != '\0'){
            ++len;
        }
        str[len] = c;
        str[len+1] = '\0';
        return str;
}

int getLetterIndex(char letters[], char letter){
    for(int i = 0; letters[i] != '\0'; ++i){
        if(letters[i] == letter){
            return i;
        }
    }
    return -1;
}

void initializeDefault(Trie *trie){
    trie->nodeCount = 0;
}

Trie* addString(Trie *trie, char str[]){
    Trie *root = trie;
    int letterIndex;
    for(int i = 0; str[i] != '\0'; ++i){
        if(trie == NULL){
            trie = (Trie*)malloc(sizeof(Trie));
            root = trie;
            letterIndex = -1;
            initializeDefault(trie);
        } else {
            letterIndex = getLetterIndex(trie->letters, str[i]);
        }
        if(letterIndex == -1){
            letterIndex = trie->nodeCount;
            appendChar(trie->letters, str[i]);
            trie->childNodes[letterIndex] = (Trie*)malloc(sizeof(Trie));
            initializeDefault(trie->childNodes[letterIndex]);
            ++trie->nodeCount;
        }
        trie = trie->childNodes[letterIndex];
    }
    trie->isWord = true;
    return root;
}

void deleteTrie(Trie *trie){
    for(int i = 0; i < trie->nodeCount; ++i){
        if(trie->childNodes[i]->nodeCount > 0){
            deleteTrie(trie->childNodes[i]);
        }
        free(trie->childNodes[i]);
        --trie->nodeCount;
    }
}


bool canBeSegmented_(Trie *trie, char* str){
    if(trie == NULL){
        printf("Trie is Empty\n");
        return false;
    }
    int letterIndex;
    Trie *root = trie;
    for(int i = 0; str[i] != '\0'; ++i){
        if(str[i] == ' '){continue;}
        letterIndex = getLetterIndex(trie->letters, str[i]);
        if(letterIndex == -1){
            if(!trie->isWord){return false;}
            trie = root;
            letterIndex = getLetterIndex(trie->letters, str[i]);
            if(letterIndex == -1){return false;}
        }
        trie = trie->childNodes[letterIndex];
    }
    return true;
}

bool canBeSegmented(char *dict[], int dict_size, char* str){
    Trie *trie = NULL;
    bool result = true;
    for(int i = 0; i < dict_size; ++i){
        trie = addString(trie, dict[i]);
    }
    result = canBeSegmented_(trie, str);
    deleteTrie(trie);
    return result;
}