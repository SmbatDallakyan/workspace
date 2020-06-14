#include <iostream>
#include "queue.hpp"

int main() {
    Queue my_queue;
    for (int i = 0; i < 10; ++i) {
        my_queue.enqueue(i * 10);
    }
    std::cout << "length = " << my_queue.getLength()<< '\n';
    for (int i = 0; i < 10; ++i) {
        std::cout << my_queue.dequeue() << '\n';
    }
    std::cout << "length = " << my_queue.getLength()<< '\n';

    return 0;
}