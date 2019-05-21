#include <iostream>
#include <map>

#include "calculator.hpp"
#include "parser.hpp"
#include "helper.hpp"

int main() {
    std::string fileName = "expression.txt";
    std::string exprStr = readFromFile(fileName);
    std::queue<std::string> queue;
    double result = 0;
    std::map<std::string, std::string> variables;
    std::map<std::string, std::string> parameters;
    parseString(exprStr, queue, variables, parameters);
    result = calculateExpr(queue, variables, parameters);
    std::cout << exprStr.substr(0, exprStr.find('|')) << " = " << result << "\n";
    return 0;
}
