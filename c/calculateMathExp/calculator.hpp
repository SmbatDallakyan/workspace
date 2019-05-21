#ifndef FUNCTIONS
#define FUNCTIONS

#include <iostream>
#include <queue>
#include <map>

using std::string;

double calculateExpr(std::queue<string>&);
double calculateExpr(string exprStr);
double calculateExpr(std::queue<string>&, std::map<string, string>, std::map<string, string>);

#endif
