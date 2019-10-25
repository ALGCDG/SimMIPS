#include <iostream>
#include <math.h>

auto add = [](const unsigned int &a, const unsigned int &b) -> unsigned int { return a + b; };
auto subtract = [](const unsigned int &a, const unsigned int &b) -> unsigned int { return a - b; };
auto multiply = [](const unsigned int &a, const unsigned int &b) -> unsigned int { return a * b; };
auto divide = [](const unsigned int &numerator, const unsigned int &denominator) -> unsigned int { return numerator / denominator; };
auto shift = [](const unsigned int &number, const unsigned int &shift) -> unsigned int { return number * pow(2, shift); };
auto band = [](const unsigned int &a, const unsigned int &b) -> unsigned int { return a & b; };
auto bor = [](const unsigned int &a, const unsigned int &b) -> unsigned int { return a | b; };
auto bxor = [](const unsigned int &a, const unsigned int &b) -> unsigned int { return a ^ b; };

// declaring a array of function pointers 
// whose return type is unsigned int and who take two unsigned ints as input
unsigned int (*alu_operations[])(const unsigned int &, const unsigned int &) = {
    add,
    subtract,
    multiply,
    divide,
    shift,
    band,
    bor,
    bxor
};

void print()
{
    std::cout << "hello world" << std::endl;
}

// // a function which takes a function as an argument
// void do_it(void(*in_f))
// {
//     in_f();
// }

int main()
{
    auto succ = [] (int x) -> int { return x + 1; };
    int (*bla)(int) = succ;
    std::cout << bla(0) << std::endl;
    std::cout << succ(5) << std::endl;
    std::cout << (alu_operations)[1](5,2) << std::endl;
    do_it(print);
    return 0;
}

// write cpu design

