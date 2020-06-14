#include <stdlib.h>
#include "stack.hpp"


Stack::Stack(){
    this->top_index = -1;
    this->stack = NULL;
    this->max_size = STACK_START_SIZE;
}

Stack::~Stack(){
    delete []this->stack;
}

void Stack::push(int object) {
    if (this->stack == NULL) {
        this->stack = new int[max_size];
    }
    if (this->top_index == max_size - 1) {
        int *tmp = this->stack;
        this->stack = new int[max_size * 2];
        for (int i = 0; i < max_size; ++i) {
            this->stack[i] = tmp[i];
        }
        max_size *= 2;
        delete []tmp;
    }

    ++(this->top_index);
    this->stack[this->top_index] = object;
}


int Stack::pop(){
    if (this->isEmpty()) {
        exit(EXIT_FAILURE);
    }
    return this->stack[this->top_index--];
}


bool Stack::isEmpty() {
    return this->top_index < 0;
}
