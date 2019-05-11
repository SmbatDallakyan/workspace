#include <iostream>
#include "functions.hpp"

int main() {
    std::string fileName = "expression.txt";
    std::string exprStr = readFromFile(fileName);
    std::queue<std::string> queue;
    double result = 0;
    parseString(exprStr, queue);
    result = calculateExpr(queue);
    std::cout << exprStr << " = " << result << "\n";
    return 0;
}
