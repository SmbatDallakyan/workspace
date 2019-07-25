#include <iostream>
#include <stack>
#include <map>
#include <cmath>

#include "calculator.hpp"
#include "helper.hpp"
#include "parser.hpp"
#include "CONSTANTS.hpp"

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
        exitWithErrorMessage(INVALID_ARGUMENTS + leftOperand + function  + rightOperand);
    }
    if (function == "log"){
        result = logN(leftOperandDouble, rightOperandDouble);
    }
    if (function == "pow"){
        result = pow(leftOperandDouble, rightOperandDouble);
    }
    if(std::isnan(result) || std::isinf(result)) {
        exitWithErrorMessage(INVALID_ARGUMENTS + function + "(" + leftOperand + "," + rightOperand + ")");
    }
    return std::to_string(result);
}

std::string calculate(std::string function, std::string operand) {
    double operandDouble = atof(operand.c_str());
    double result = 0;
    //  Calculate using degree
    operandDouble = operandDouble * M_PI / 180;
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

std::string getVariableValue(std::string variableName, std::map<std::string, std::string> variables) {
    std::map<std::string, std::string>::iterator variable;
    for (variable = variables.begin(); variable != variables.end(); ++variable) {
        if(variable->first == variableName) {
            return variable->second;
        }
    }
    return "";
}

double calculateExpr(std::queue<std::string>& exprQueue) {
    std::map<std::string, std::string> variables;
    std::map<std::string, std::string> parameters;
    return calculateExpr(exprQueue, variables, parameters);
}

double calculateExpr(std::string exprStr) {
    std::queue<std::string> queue;
    std::map<std::string, std::string> variables;
    std::map<std::string, std::string> parameters;
    parseString(exprStr, queue, variables, parameters);
    return calculateExpr(queue, variables, parameters);
}

double calculateExpr(std::queue<std::string>& exprQueue,
                    std::map<std::string, std::string> variables,
                    std::map<std::string, std::string> parameters) {
    if(exprQueue.empty()) {
        exitWithErrorMessage(INVALID_EXPRESSION);
    }
    std::queue<std::string> outputQueue;
    std::stack<std::string> operatorStack;
    std::string token = "";
    std::string rightOperend = "";
    std::string leftOperend = "";
    std::string value = "";
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
                        (getOperatorPrecedence(token) == getOperatorPrecedence(operatorStack.top()) &&
                        isLeftAssociative(operatorStack.top()))
                    )) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                operatorStack.push(token);
                break;
            case LEFT_PAREN_ID:
                operatorStack.push(token);
                if(exprQueue.front() == ")") {
                    exitWithErrorMessage(INVALID_PARENS);
                }
                break;
            case RIGHT_PAREN_ID:
                if(operatorStack.empty()) {
                    exitWithErrorMessage(INVALID_PARENS);
                }
                while(!operatorStack.empty() && getTokenId(operatorStack.top()) != LEFT_PAREN_ID) {
                    outputQueue.push(operatorStack.top());
                    operatorStack.pop();
                }
                if(operatorStack.empty()) {
                    exitWithErrorMessage(INVALID_PARENS);
                } else {
                    operatorStack.pop();
                    token = "*";
                    if (!exprQueue.empty() && exprQueue.front() == "(") {
                            while(!operatorStack.empty() && (
                                    isFunction(operatorStack.top()) ||
                                    getOperatorPrecedence(token) < getOperatorPrecedence(operatorStack.top()) ||
                                    (getOperatorPrecedence(token) == getOperatorPrecedence(operatorStack.top()) &&
                                    isLeftAssociative(operatorStack.top()))
                                )) {
                                outputQueue.push(operatorStack.top());
                                operatorStack.pop();
                            }
                        operatorStack.push(token);
                    }
                }
                break;
            case COMMA_ID:
                while(!operatorStack.empty() && getTokenId(operatorStack.top()) != LEFT_PAREN_ID) {
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
            exitWithErrorMessage(INVALID_PARENS);
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
                if(operatorStack.empty()) {
                    exitWithErrorMessage(INVALID_EXPRESSION);
                }
                rightOperend = operatorStack.top();
                operatorStack.pop();
                if(token == "-" && (operatorStack.empty() || !isDigit(operatorStack.top()) )){
                    leftOperend = "0";
                } else if (operatorStack.empty()) {
                    exitWithErrorMessage(INVALID_EXPRESSION);
                } else {
                    leftOperend = operatorStack.top();
                    operatorStack.pop();
                }
                token = calculate(token, leftOperend, rightOperend);
                operatorStack.push(token);
                break;
            case FUNCTION_ID:
                if (operatorStack.empty()) {
                    exitWithErrorMessage(INVALID_EXPRESSION);
                }
                rightOperend = operatorStack.top();
                operatorStack.pop();
                if(getArgumentCount(token) == 2) {
                    if (operatorStack.empty()) {
                        exitWithErrorMessage(INVALID_EXPRESSION);
                    }
                    leftOperend = operatorStack.top();
                    operatorStack.pop();
                    token = calculate(token, leftOperend, rightOperend);
                } else {
                    token = calculate(token, rightOperend);
                }
                operatorStack.push(token);
                break;
            case VARIABLE_ID:
                value = getVariableValue(token, variables);
                if(value == "") {
                    exitWithErrorMessage(UNDEFINED_VARIABLE + token);
                }
                operatorStack.push(value);
                break;
            case PARAMETER_ID:
                value = getVariableValue(token, parameters);
                if(value == "") {
                    exitWithErrorMessage(UNDEFINED_VARIABLE + token);
                }
                operatorStack.push(value);
                break;
            default:
                break;
        }
    }
    rightOperend = operatorStack.top();
    operatorStack.pop();
    if(!operatorStack.empty()) {
        exitWithErrorMessage(INVALID_EXPRESSION);
    }
    result = atof(rightOperend.c_str());
    return result;
}
