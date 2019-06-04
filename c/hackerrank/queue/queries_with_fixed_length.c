#include <assert.h>
#include <limits.h>
#include <math.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char* readline();
char** split_string(char*);

typedef struct numWithIndex {
    int value;
    int index;
} numWithIndex;

// Complete the solve function below.

// Please store the size of the integer array to be returned in result_count pointer. For example,
// int a[3] = {1, 2, 3};
//
// *result_count = 3;
//
// return a;
//

numWithIndex getMax(int* arr, int startIndex, int endIndex){
    numWithIndex result;
    result.value = arr[startIndex];
    result.index = startIndex;
    for(int i = startIndex + 1; i <= endIndex; ++i){
        if(arr[i] >= result.value){
            result.value = arr[i];
            result.index = i;
        }
    }
    return result;
}

int* solve(int arr_count, int* arr, int queries_count, int* queries, int* result_count) {
    *result_count = queries_count;
    int* result = malloc(queries_count * sizeof(int));
    for(int i = 0; i < queries_count; ++i){
        numWithIndex maxNum;
        maxNum = getMax(arr, 0, queries[i] - 1);
        result[i] = maxNum.value;
        for(int j = 1; j <= arr_count - queries[i]; ++j){
            if(maxNum.index < j){
                maxNum = getMax(arr, j, j + queries[i] - 1);
            } else {
                if(arr[j] >= maxNum.value){
                    maxNum.value = arr[j];
                    maxNum.index = j;
                }
            }
            result[i] = maxNum.value < result[i] ? maxNum.value : result[i];
        }
    }
    return result;
}

int main()
{
    FILE* fptr = fopen(getenv("OUTPUT_PATH"), "w");

    char** nq = split_string(readline());

    char* n_endptr;
    char* n_str = nq[0];
    int n = strtol(n_str, &n_endptr, 10);

    if (n_endptr == n_str || *n_endptr != '\0') { exit(EXIT_FAILURE); }

    char* q_endptr;
    char* q_str = nq[1];
    int q = strtol(q_str, &q_endptr, 10);

    if (q_endptr == q_str || *q_endptr != '\0') { exit(EXIT_FAILURE); }

    char** arr_temp = split_string(readline());

    int* arr = malloc(n * sizeof(int));

    for (int arr_itr = 0; arr_itr < n; arr_itr++) {
        char* arr_item_endptr;
        char* arr_item_str = *(arr_temp + arr_itr);
        int arr_item = strtol(arr_item_str, &arr_item_endptr, 10);

        if (arr_item_endptr == arr_item_str || *arr_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(arr + arr_itr) = arr_item;
    }

    int arr_count = n;

    int* queries = malloc(q * sizeof(int));

    for (int queries_itr = 0; queries_itr < q; queries_itr++) {
        char* queries_item_endptr;
        char* queries_item_str = readline();
        int queries_item = strtol(queries_item_str, &queries_item_endptr, 10);

        if (queries_item_endptr == queries_item_str || *queries_item_endptr != '\0') { exit(EXIT_FAILURE); }

        *(queries + queries_itr) = queries_item;
    }

    int queries_count = q;

    int result_count;
    int* result = solve(arr_count, arr, queries_count, queries, &result_count);

    for (int result_itr = 0; result_itr < result_count; result_itr++) {
        fprintf(fptr, "%d", *(result + result_itr));

        if (result_itr != result_count - 1) {
            fprintf(fptr, "\n");
        }
    }

    fprintf(fptr, "\n");

    fclose(fptr);

    return 0;
}

char* readline() {
    size_t alloc_length = 1024;
    size_t data_length = 0;
    char* data = malloc(alloc_length);

    while (true) {
        char* cursor = data + data_length;
        char* line = fgets(cursor, alloc_length - data_length, stdin);

        if (!line) { break; }

        data_length += strlen(cursor);

        if (data_length < alloc_length - 1 || data[data_length - 1] == '\n') { break; }

        size_t new_length = alloc_length << 1;
        data = realloc(data, new_length);

        if (!data) { break; }

        alloc_length = new_length;
    }

    if (data[data_length - 1] == '\n') {
        data[data_length - 1] = '\0';
    }

    data = realloc(data, data_length);

    return data;
}

char** split_string(char* str) {
    char** splits = NULL;
    char* token = strtok(str, " ");

    int spaces = 0;

    while (token) {
        splits = realloc(splits, sizeof(char*) * ++spaces);
        if (!splits) {
            return splits;
        }

        splits[spaces - 1] = token;

        token = strtok(NULL, " ");
    }

    return splits;
}
