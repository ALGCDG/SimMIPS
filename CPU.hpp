// CPU
#include <iostream>
#include <map>
#include "simulated_memory.hpp"
#include "register.hpp"
#include "J.hpp"
#include "I.hpp"
#include "R.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

class CPU
{
    private:
    // references to processor components
    simulated_memory memory;
    simulated_register registers;
    R_TYPE r;
    I_TYPE i;
    J_TYPE j;
    //static std::map<uchar, R_OPCODE> R_OPCODES;
    //std::map<uchar, R_OPCODE> R_OPCODES;

    static std::map<uchar, I_OPCODE> I_OPCODES;
    static std::map<uchar, J_OPCODE> J_OPCODES;
    void interpret_instruction(const uint &instruction);

    public:
    int run(); // returns exit code
    CPU(const std::string &binary_file_path/*file stream for binary instructions*/);
};
