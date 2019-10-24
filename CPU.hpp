// CPU
#include <iostream>
#include <map>
#include "register.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*R_OPCODE)(const uchar &, const uchar &, const uchar &, const uchar &);
// input arguments are rs(5), rt(5), rd(5), shamt(5)
typedef void (*I_OPCODE)(const uchar &, const uchar &, const uint &);
// input arguments are rs(5), rt(5), immediate(16)
typedef void (*J_OPCODE)(const uint &);
// input arguments are address(26)

class CPU : simulated_register
{
    // private:
    public:
    // memory;
    // simulated_register registers;
    static std::map<uchar, R_OPCODE> R;
    static std::map<uchar, I_OPCODE> I;
    static std::map<uchar, J_OPCODE> J;

    public:
    int run(); // returns exit code
    CPU(/*file stream for binary instructions*/);
};