#include <iostream>
#include <queue>
#include <map>
#include <algorithm>
#include <bits/stdc++.h>

#include "helper.hpp"
#include "CONSTANTS.hpp"

using std::string;
using std::map;

void initializeVariables(string &variableNames,
                        string &variableValues,
                        map<string, string> &variables,
                        map<string, string> &parameters) {
    std::stringstream names(variableNames);
    std::stringstream values(variableValues);
    string name = "";
    string value = "";
    while(std::getline(names, name, ',') && std::getline(values, value, ',') ){
        if(isVariable(name)) {
            variables.insert(std::pair<string, string>(name, value));
        } else if (isParameter(name)) {
            parameters.insert(std::pair<string, string>(name, value));
        } else {
            exitWithErrorMessage("invalid Variables");
        }
    }
    return;
}

std::queue<string> parseString(string str,
                                std::queue<string> &queue,
                                map<string, string> &variables,
                                map<string, string> &parameters) {
    str.erase(std::remove_if(str.begin(), str.end(), isspace), str.end());
    string variableNames = "";
    string variableValues = "";
    string expression = "";
    string token = "";
    std::stringstream check1(str);
    expression = std::getline(check1, token, '|') ? token : "";
    variableNames = std::getline(check1, token, '|') ? token : "";
    variableValues = std::getline(check1, token, '|') ? token : "";
    initializeVariables(variableNames, variableValues, variables, parameters);
    str = expression;
    int strLength = str.length();
    if(!strLength) {
        exitWithErrorMessage(INVALID_EXPRESSION);
    }
    string currentNumber = "";
    string currentfunction = "";
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
                queue.push(string(1, str[i]));
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
            queue.push(string(1, str[i]));
            int nextTokenId = getTokenId(string(1, str[i+1]));
            if(i < strLength - 1 && (nextTokenId == LEFT_PAREN_ID || isalpha(str[i+1]))) {
                queue.push("*");
            }
        } else {
            exitWithErrorMessage(INVALID_EXPRESSION);
        }
    }
    if (currentNumber.length()){
        queue.push(currentNumber);
    }
    return queue;
}
