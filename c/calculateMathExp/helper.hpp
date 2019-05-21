#ifndef HELPER
#define HELPER

#include <iostream>

int getTokenId(std::string);
bool isParameter(std::string);
bool isVariable(std::string);
bool isDigit(std::string);
bool isFunction(std::string, int indexToStart = 0);
void exitWithErrorMessage(std::string);
std::string getFunction(std::string, int indexToStart = 0);
std::string readFromFile(std::string);

#endif
