#include "Trie.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(){
    char *dict[] = {"hello","blt"};
    int dict_size = sizeof(dict)/sizeof(dict[0]);
    char str[] = "hello";

    if( canBeSegmented(dict, dict_size, str) ){
        printf("YES\n");
    } else {
        printf("NO\n");
    }
    return 0;
}