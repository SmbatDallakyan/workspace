#include <iostream>
#include <queue>

#ifndef FUNCTIONS
#define FUNCTIONS

std::string readFromFile(std::string);
std::queue<std::string> parseString(std::string, std::queue<std::string>&);
double calculateExpr(std::queue<std::string>&);

#endif
