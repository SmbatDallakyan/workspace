#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <string>
#include <queue>
#include <stack>
#include <cmath>
#include <algorithm>
#include "functions.hpp"

#define DIGIT_ID 1
#define OPERATOR_ID 2
#define LEFT_PAREN_ID 3
#define RIGHT_PAREN_ID 4
#define FUNCTION_ID 5
#define VARIABLE_ID 6
#define PARAMETER_ID 7
#define COMMA_ID 8

void exitWithErrorMessage(std::string message) {
    std::cerr << message << "\n";
    exit(1);
}

std::string readFromFile(std::string fileName) {
    std::ifstream infile(fileName.c_str());
    std::string sLine;
    if (infile.good()) {
        getline(infile, sLine);
    } else {
        exitWithErrorMessage("Error, Can't read file with name " + fileName);
    }
    infile.close();
    return sLine;
}

std::string getFunction(std::string token, int indexToStart = 0) {
    const std::string functions[] = {"sin", "cos", "tg", "ctg", "pow", "log"};
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

bool isDigit(std::string str) {
    if (!str.length() || (str[0] != '-' && !isdigit(str[0]))) {
        return false;
    }
    for (unsigned int i = 1; i < str.length(); ++i) {
        if(!isdigit(str[i]) && str[i] != '.') {
            return false;
        }
    }
    return true;
}

int getArgumentCount(std::string token, int indexToStart = 0) {
    token = getFunction(token, indexToStart);
    const std::string functionsWithOneArg[] = {"sin", "cos", "tg", "ctg"};
    const std::string functionsWithTwoArg[] = {"pow", "log"};
    for(const std::string &function : functionsWithOneArg) {
        if(token == function) {
            return 1;
        }
    }
    for(const std::string &function : functionsWithTwoArg) {
        if(token == function) {
            return 2;
        }
    }
    return 0;
}

int getTokenId(std::string token) {
    if (token.length() == 1) {
        switch (token[0]){
            case '+':
            case '-':
            case '*':
            case '/':
            case '^':
                return OPERATOR_ID;
            case '(':
                return LEFT_PAREN_ID;
            case ')':
                return RIGHT_PAREN_ID;
            case ',':
                return COMMA_ID;
        }
    }
    if (isDigit(token)) {
        return DIGIT_ID;
    }
    if (isFunction(token)) {
        return FUNCTION_ID;
    }
    if (token.length() == 1 &&
        ((token[0] >= 65 && token[0] <= 79) || (token[0] >= 97 && token[0] <= 111))) {
        return PARAMETER_ID;
    }
    if (token.length() == 1 &&
        ((token[0] >= 80 && token[0] <= 90) || (token[0] >= 112 && token[0] <= 122))) {
        return VARIABLE_ID;
    }
    return 0;
}

std::queue<std::string> parseString(std::string str, std::queue<std::string> &queue) {
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    int strLength = str.length();
    std::string currentNumber = "";
    std::string currentfunction = "";
    for(int i = 0; i < strLength; ++i) {
        if(isdigit(str[i]) || str[i] == '.') {
            currentNumber += str[i];
        } else if (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-'
                || str[i] == '*' || str[i] == '/' || str[i] == '^' || str[i] == ',') {
            if (currentNumber.length()){
                queue.push(currentNumber);
                currentNumber = "";
            }
            if (!queue.empty() && str[i] == '(' &&
                (((isalpha(queue.back()[0]) && !isFunction(queue.back())) ||
                isDigit(queue.back())))) {
                queue.push("*");
            }
            if (str[i] == '-' && (queue.empty() || queue.back() == "(" || queue.back() == "," )) {
                queue.push("-1");
                queue.push("*");
            } else {
                queue.push(std::string(1, str[i]));
            }
            if (i < strLength - 1 && str[i] == ')' &&
                (isalpha(str[i+1]) || isdigit(str[i+1]))) {
                queue.push("*");
            }
        } else if(isFunction(str, i)) {
            if (currentNumber.length()){
                queue.push(currentNumber);
                currentNumber = "";
                queue.push("*");
            }
            currentfunction = getFunction(str, i);
            queue.push(currentfunction);
            i += currentfunction.length()-1;
        } else if(isalpha(str[i])) {
            if (currentNumber.length()){
                queue.push(currentNumber);
                currentNumber = "";
                queue.push("*");
            }
            queue.push(std::string(1, str[i]));
            int nextTokenId = getTokenId(std::string(1, str[i+1]));
            if(i < strLength - 1 && (nextTokenId == LEFT_PAREN_ID || isalpha(str[i+1]))) {
                queue.push("*");
            }
        }
    }
    if (currentNumber.length()){
        queue.push(currentNumber);
    }
    return queue;
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

double logN(double base, double x) {
    return std::log(x) / std::log(base);
}

std::string calculate(std::string function, std::string leftOperand, std::string rightOperand) {
    double rightOperandDouble = atof(rightOperand.c_str());
    double leftOperandDouble = atof(leftOperand.c_str());
    double result = 0;
    switch (function[0]) {
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
    }
    if(std::isnan(result) || std::isinf(result)) {
        exitWithErrorMessage("Error, invalid arguments >> " + leftOperand + function  + rightOperand);
    }
    if (function == "log"){
        result = logN(leftOperandDouble, rightOperandDouble);
    }
    if (function == "pow"){
        result = pow(leftOperandDouble, rightOperandDouble);
    }
    if(std::isnan(result) || std::isinf(result)) {
        exitWithErrorMessage("Error, invalid function arguments >> " +
            function + "(" + leftOperand + "," + rightOperand + ")");
    }
    return std::to_string(result);
}

std::string calculate(std::string function, std::string operand) {
    double operandDouble = atof(operand.c_str());
    double result = 0;
    //  Calculate using degree
    // operandDouble = operandDouble * M_PI / 180;
    if (function == "sin") {
        result = sin(operandDouble);
    } else if (function == "cos") {
        result = cos(operandDouble);
    } if (function == "tg") {
        result = tan(operandDouble);
    } if (function == "ctg") {
        result = tan(M_PI_2 - operandDouble);
    }
    return std::to_string(result);
}

// --- TO DO --- Implement get parameters and variables
std::string getParameterValue(std::string paramName){
    return "10";
}
double calculateExpr(std::string exprStr) {
    std::queue<std::string> queue;
    parseString(exprStr, queue);
    return calculateExpr(queue);
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
            case PARAMETER_ID:
            case VARIABLE_ID:
            case DIGIT_ID:
                outputQueue.push(token);
                break;
            case OPERATOR_ID:
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
            case LEFT_PAREN_ID:
                operatorStack.push(token);
                break;
            case RIGHT_PAREN_ID:
                if(operatorStack.empty()) {
                    exitWithErrorMessage("Error: Invalid parens: Please enter the valid expression\n");
                }
                while(!operatorStack.empty() && getTokenId(operatorStack.top()) != LEFT_PAREN_ID) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if(operatorStack.empty()) {
                    exitWithErrorMessage("Error: Invalid parens: Please enter the valid expression\n");
                } else {
                    operatorStack.pop();
                }
                break;
            case COMMA_ID:
                while(getTokenId(operatorStack.top()) != LEFT_PAREN_ID) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                break;
            case FUNCTION_ID:
                operatorStack.push(token);
                break;
        }
    }
    while (!operatorStack.empty()) {
        token = operatorStack.top();
        if (token == "(") {
            exitWithErrorMessage("Errore: Invalid opening paren");
        }
        outputQueue.push(token);
        operatorStack.pop();
    }

    while (!outputQueue.empty()) {
        token = outputQueue.front();
        outputQueue.pop();
        switch (getTokenId(token)) {
            case DIGIT_ID:
                operatorStack.push(token);
                break;
            case OPERATOR_ID:
                rightOperend = operatorStack.top();
                operatorStack.pop();
                if(token == "-" && (operatorStack.empty() || !isDigit(operatorStack.top()) )){
                    leftOperend = "0";
                } else {
                    leftOperend = operatorStack.top();
                    operatorStack.pop();
                }
                token = calculate(token, leftOperend, rightOperend);
                operatorStack.push(token);
                break;
            case FUNCTION_ID:
                rightOperend = operatorStack.top();
                operatorStack.pop();
                if(getArgumentCount(token) == 2) {
                    leftOperend = operatorStack.top();
                    operatorStack.pop();
                    token = calculate(token, leftOperend, rightOperend);
                } else {
                    token = calculate(token, rightOperend);
                }
                operatorStack.push(token);
                break;
            case VARIABLE_ID:
            case PARAMETER_ID:
                operatorStack.push(getParameterValue(token));
                break;
            default:
                break;
        }
    }
    rightOperend = operatorStack.top();
    operatorStack.pop();
    result = atof(rightOperend.c_str());
    return result;
}
