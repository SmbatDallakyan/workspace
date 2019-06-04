#ifndef TRIE
#define TRIE

#include <stdbool.h>
#define LETTER_COUNT 26

typedef struct Trie {
    char letters [LETTER_COUNT];
    struct Trie* childNodes[LETTER_COUNT];
    int nodeCount;
    bool isWord;
} Trie;

void initializeDefault(Trie *trie);
Trie* addString(Trie *trie, char str[]);
bool canBeSegmented(char *dict[], int dict_size, char* str);

#endif