#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <cmath>

#include "functions.hpp"

#define DIGIT 1
#define OPERATOR 2
#define LEFT_PAREN 3
#define RIGHT_PAREN 4
#define FUNCTION 5

std::string readFromFile(std::string fileName) {
    std::ifstream infile(fileName.c_str());
    std::string sLine;
    if (infile.good()) {
        getline(infile, sLine);
    } else {
        std::cerr << "Can't read file " << fileName << "\n";
        exit(1);
    }
    infile.close();
    return sLine;
}

std::string getFunction(std::string token, int indexToStart = 0) {
    const std::string functions[] = {"sin", "cos"};
    for(const std::string &function : functions) {
        if(token.substr(indexToStart, function.length()) == function) {
            return function;
        }
    }
    return "";
}

bool isFunction(std::string token, int indexToStart = 0) {
    return getFunction(token, indexToStart).length();
}

std::queue<std::string> parseString(std::string str, std::queue<std::string> &queue) {
    int strLength = str.length();
    std::string currentNumber = "";
    std::string currentfunction = "";
    for(int i = 0; i < strLength; ++i) {
        if(isdigit(str[i]) || str[i] == '.') {
            currentNumber += str[i];
        } else if (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-'
                || str[i] == '*' || str[i] == '/' || str[i] == '^') {
            if (currentNumber.length()){
                queue.push(currentNumber);
            }
            queue.push(std::string(1, str[i]));
            currentNumber = "";
        } else if(isFunction(str, i)) {
            currentfunction = getFunction(str, i);
            queue.push(currentfunction);
            i += currentfunction.length()-1;
        }
    }
    if (currentNumber.length()){
        queue.push(currentNumber);
    }
    return queue;
}

int getTokenId(std::string token) {
    switch (token[0]){
        case '+':
        case '-':
        case '*':
        case '/':
        case '^':
            return OPERATOR;
        case '(':
            return LEFT_PAREN;
        case ')':
            return RIGHT_PAREN;
    }
    if(isdigit(token[0])) {
        return DIGIT;
    }
    if (isFunction(token)) {
        return FUNCTION;
    }
    return 0;
}

int getOperatorPrecedence(char oper) {
    switch (oper) {
    case '+':
    case '-':
        return 2;
    case '*':
    case '/':
        return 3;
    case '^':
        return 4;
    default:
        return 0;
    }
}

int getOperatorPrecedence(std::string oper) {
    return getOperatorPrecedence(oper[0]);
}

bool isLeftAssociative(std::string token) {
    const std::string leftAssociativeOperators[] = {"+", "-", "*", "/"};
    for(const std::string &oper : leftAssociativeOperators) {
        if(token == oper) {
            return true;
        }
    }
    return false;
}

std::string calculate(std::string rightOperand, std::string leftOperand, std::string oper) {
    double rightOperandDouble = atof(rightOperand.c_str());
    double leftOperandDouble = atof(leftOperand.c_str());
    double result = 0;
    switch (oper[0]) {
    case '+':
        result = leftOperandDouble + rightOperandDouble;
        break;
    case '-':
        result = leftOperandDouble - rightOperandDouble;
        break;
    case '*':
        result = leftOperandDouble * rightOperandDouble;
        break;
    case '/':
        result = leftOperandDouble / rightOperandDouble;
        break;
    case '^':
        result = pow(leftOperandDouble, rightOperandDouble);
        break;
    default:
        break;
    }
    return std::to_string(result);
}

std::string calculate(std::string operand, std::string function) {
    double operandDouble = atof(operand.c_str());
    double result = 0;
    if (function == "sin") {
        result = sin(operandDouble*3.14159/180);
    }
    if (function == "cos") {
        result = cos(operandDouble);
    }
    return std::to_string(result);
}

double calculateExpr(std::queue<std::string>& exprQueue) {
    std::queue<std::string> outputQueue;
    std::stack<std::string> operatorStack;
    std::string token = "";
    std::string rightOperend = "";
    std::string leftOperend = "";
    double result = 0;
    while(!exprQueue.empty()){
        token = exprQueue.front();
        exprQueue.pop();
        switch (getTokenId(token)) {
            case DIGIT : {
                outputQueue.push(token);
                break;
            }
            case OPERATOR : {
                while(!operatorStack.empty() && operatorStack.top() != "(" && (
                        isFunction(operatorStack.top()) ||
                        getOperatorPrecedence(token) < getOperatorPrecedence(operatorStack.top()) ||
                        (getOperatorPrecedence(token) == getOperatorPrecedence(operatorStack.top()) && isLeftAssociative(operatorStack.top()))
                    )) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;
            }
            case LEFT_PAREN : {
                operatorStack.push(token);
                break;
            }
            case RIGHT_PAREN : {
                while(getTokenId(operatorStack.top()) != LEFT_PAREN) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if(getTokenId(operatorStack.top()) == LEFT_PAREN) {
                    operatorStack.pop();
                }
                break;
            }
            case FUNCTION : {
                operatorStack.push(token);
                break;
            }
        }
    }
    while (!operatorStack.empty()) {
        outputQueue.push(operatorStack.top());
        operatorStack.pop();
    }

    while (!outputQueue.empty()) {
        token = outputQueue.front();
        std::cout << outputQueue.front() << "  ";
        outputQueue.pop();
        switch (getTokenId(token)) {
            case DIGIT:
                operatorStack.push(token);
                break;
            case OPERATOR:
                rightOperend = operatorStack.top();
                operatorStack.pop();
                leftOperend = operatorStack.top();
                operatorStack.pop();
                token = calculate(rightOperend, leftOperend, token);
                operatorStack.push(token);
                break;
            case FUNCTION:
                rightOperend = operatorStack.top();
                operatorStack.pop();
                token = calculate(rightOperend, token);
                operatorStack.push(token);
            default:
                break;
        }
    }
    rightOperend = operatorStack.top();
    operatorStack.pop();
    std::cout <<  "\n";
    result = atof(rightOperend.c_str());
    return result;
}
