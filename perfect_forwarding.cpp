// Demonstration of perfect forwarding using std::forward
#include <iostream>
#include "debug_print.h"

void process(int& x)
{
    std::cout << "Lvalue processed: " << x << std::endl;
}

void process(int&& x)
{
    std::cout << "Rvalue processed: " << x << std::endl;
}

template <typename T>
void wrapper(T&& arg)
{
    // Forward the argument to another function
    process(std::forward<T>(arg));
}

int main()
{
    std::cout << "=== Perfect Forwarding Demo ===" << std::endl;

    int a = 10;
    std::cout << "\n1. Passing lvalue:" << std::endl;
    wrapper(a); // should call lvalue version

    std::cout << "\n2. Passing rvalue:" << std::endl;
    wrapper(20); // should call rvalue version

    return 0;
}

// Q: What does perfect forwarding do in real-world development?
// A: It allows functions to accept arguments of any value category (lvalue, rvalue)
//    and forward them to other functions without losing their original value category.
//    This is particularly useful in generic programming and move semantics.
// Q: What about "xvalue" in C++?
// A: "xvalue" is a glvalue (i.e. generalized lvalue) that is about to be destroyed.
//    It's a kind of rvalue that can be moved from.
//    In perfect forwarding, std::forward<T>(arg) will forward an xvalue as an rvalue.