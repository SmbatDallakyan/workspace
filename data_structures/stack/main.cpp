#include <iostream>
#include "stack.hpp"

int main() {
    Stack st;
    for (int i = 1; i <= 10; i++) {
        st.push(i);
    }
    while (!st.isEmpty()) {
        std::cout << "------ " << st.pop() << " ------\n";
    }
    return 0;
}