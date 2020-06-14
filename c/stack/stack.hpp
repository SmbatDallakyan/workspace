#include <iostream>

#ifndef MY_STACK
#define MY_STACK
#define STACK_START_SIZE 100



class Stack {
    public:
        Stack();
        ~Stack();
        void push(int Object);
        int pop();
        bool isEmpty();

    private:
        int *stack;
        int top_index;
        int max_size;
};

#endif