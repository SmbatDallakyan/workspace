#include <iostream>
#include "functions.hpp"

int main() {
    std::string fileName = "expression.txt";
    std::string exprStr = readFromFile(fileName);
    std::queue<std::string> queue;
    queue = parseString(exprStr, queue);
    while(!queue.empty()){
        std::cout<<queue.front()<<"\n";
        queue.pop();
    }
    return 0;
}
