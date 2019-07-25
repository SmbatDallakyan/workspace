#include <iostream>
#include <fstream>

#include "helper.hpp"
#include "CONSTANTS.hpp"

void exitWithErrorMessage(std::string message) {
    const std::string red("\033[0;31m");
    const std::string reset("\033[0m");
    std::cerr << red << "\n" << message << reset << "\n";
    exit(1);
}

bool isParameter(std::string variableName) {
    return variableName.length() == 1 &&
            ((variableName[0] >= 65 && variableName[0] <= 79) ||
            (variableName[0] >= 97 && variableName[0] <= 111));
}

bool isVariable(std::string variableName) {
    return variableName.length() == 1 &&
            ((variableName[0] >= 80 && variableName[0] <= 90) ||
            (variableName[0] >= 112 && variableName[0] <= 122));
}

std::string getFunction(std::string token, int indexToStart) {
    const std::string functions[] = {"sin", "cos", "tg", "ctg", "pow", "log"};
    for(const std::string &function : functions) {
        if(token.substr(indexToStart, function.length()) == function) {
            return function;
        }
    }
    return "";
}

bool isFunction(std::string token, int indexToStart) {
    return getFunction(token, indexToStart).length();
}

bool isDigit(std::string str) {
    int countOfDot = 0;
    int strLength = str.length();
    if (!strLength || (str[0] != '-' && !isdigit(str[0]))) {
        return false;
    }
    if (strLength > 1 && str[0] == '-' && !isdigit(str[1])) {
        return false;
    }
    if (strLength == 1 && str[0] == '-') {
        return false;
    }
    for (unsigned int i = 1; i < str.length(); ++i) {
        if(str[i] == '.') {
            ++countOfDot;
        }
        if((!isdigit(str[i]) && str[i] != '.') ||
            countOfDot > 1) {
            return false;
        }
    }
    return true;
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
    if (isParameter(token)) {
        return PARAMETER_ID;
    }
    if (isVariable(token)) {
        return VARIABLE_ID;
    }
    return 0;
}

std::string readFromFile(std::string fileName) {
    std::ifstream infile(fileName.c_str());
    std::string result = "";
    if (infile.good()) {
        getline(infile, result);
    } else {
        exitWithErrorMessage(ERROR_FILE_READ + fileName);
    }
    infile.close();
    return result;
}
