#include <iostream>
#include <queue>
#include <map>

#ifndef FUNCTIONS
#define FUNCTIONS

std::string readFromFile(std::string);
std::queue<std::string> parseString(std::string,
                                    std::queue<std::string>&,
                                    std::map<std::string, std::string>&,
                                    std::map<std::string, std::string>&);
double calculateExpr(std::queue<std::string>&);
double calculateExpr(std::string exprStr);
double calculateExpr(std::queue<std::string>&,
                    std::map<std::string, std::string>,
                    std::map<std::string, std::string>);

#endif
