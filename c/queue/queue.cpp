#include <iostream>
#include <stdlib.h>
#include "queue.hpp"

Queue::Queue():
head(NULL),
tail(NULL),
length(0)
{};

Queue::~Queue(){
    while (!isEmpty()) {
        dequeue();
    }
}

void Queue::enqueue(int data) {
    node *newNode = new node();
    newNode->data = data;
    newNode->next = tail;
    newNode->prev = NULL;

    if (tail == NULL) {
        head = newNode;
    } else {
        tail->prev = newNode;
    }
    tail = newNode;
    ++length;
}

int Queue::dequeue() {
    if (isEmpty()) {
        std::cout << "Queue is empty\nExit with failure\n";
        exit(EXIT_FAILURE);
    }
    node *currentNode = head;
    int data = currentNode->data;
    head = head->prev;
    --length;
    delete currentNode;
    return data;
}

bool Queue::isEmpty() {
    return length == 0;
}

int Queue::getLength() {
    return length;
}
