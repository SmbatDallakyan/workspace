#include <stdlib.h>
#include <iostream>
#include <fstream>
#include <queue>

#include "functions.hpp"

std::string readFromFile(std::string fileName) {
    std::ifstream infile(fileName.c_str());
    std::string sLine;
    if (infile.good()) {
        getline(infile, sLine);
    } else {
        std::cerr << "Exception opening/reading file\n";
        exit(1);
    }
    infile.close();
    return sLine;
}

std::queue<std::string> parseString(std::string str, std::queue<std::string> queue) {
    int strLength = str.length();
    std::queue<std::string> queue;
    std::string currentNumber = "";
    for(int i = 0; i < strLength; ++i) {
        if(isdigit(str[i]) || str[i] == '.') {
            currentNumber += str[i];
        } else if (str[i] == '(' || str[i] == ')' || str[i] == '+' || str[i] == '-' || str[i] == '*' || str[i] == '/') {
            if (currentNumber.length()){
                queue.push(currentNumber);
            }
            queue.push(std::string(1, str[i]));
            currentNumber = "";
        }
    }
    if (currentNumber.length()){
        queue.push(currentNumber);
    }
    return queue;
}
