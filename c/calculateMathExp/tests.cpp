#include "iostream"
#include "functions.hpp"
#include <cmath>

static std::string expressions[] = {
    "5+7",
    "-5-7",
    "2*(-log(2,8) + 2)",
    "2+(-3log(3,9)+7)",
    "-2log(4,2*8)",
    "-2*2-3log(4,2*8)",
    "25+35*(-16+7)",
    "-sin(-30)+7",
    "-sin(-30+60)+7",
    "cos(sin(30) *  120)",
    "cos(6*(10sin(30) + 10cos(60)))",
    "(log(pow(sin(1), -cos(2)), tg(1) / ctg(2)) + 4) * pow(2.5, 10)"
};

static double results[] = {
    12,
    -12,
    -2,
    3,
    -4,
    -10,
    -290,
    7.5,
    6.5,
    0.5,
    0.5,
    20699.04327
};

void runTests() {
    const std::string red("\033[0;31m");
    const std::string green("\033[0;32m");
    const std::string reset("\033[0m");
    int testsCount = sizeof(expressions)/sizeof(expressions[0]);
    if(testsCount != sizeof(results)/sizeof(results[0])) {
        std::cout << "Test cases and results are not maches\n";
        return;
    }
    double result = 0;
    std::cout << "\nExpression\t|\t" << "Expected result \t|\t" << "Actual result \n";
    int fails = 0;
    int pass = 0;
    for (unsigned int i = 0; i < sizeof(expressions)/sizeof(expressions[0]); ++i) {
        result = calculateExpr(expressions[i]);
        std::cout << expressions[i] << " | " << results[i] << " | " << result;
        if (round(result * 100000) / 100000 != results[i]) {
            std::cout << red <<" | Fail\n" << reset;
            ++fails;
        } else {
            std::cout << green << " | Pass\n" << reset;
            ++pass;
        }
    }
    std::cout<<"\nTest cases : " << pass + fails <<'\n';
    std::cout<<green<<"Pass : " << pass << reset << '\n';
    std::cout<<red<<"Fail : " << fails << reset <<"\n\n";
}

int main() {
    runTests();
    return 0;
}
