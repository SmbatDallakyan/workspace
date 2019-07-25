#ifndef PARSER
#define PARSER

#include <iostream>
#include <map>
#include <queue>

using std::string;

void initializeVariables(string &variableNames,
                        string &variableValues,
                        std::map<string, string> &variables,
                        std::map<string, string> &parameters);

std::queue<string> parseString(string str,
                                std::queue<string> &queue,
                                std::map<string, string> &variables,
                                std::map<string, string> &parameters);

#endif