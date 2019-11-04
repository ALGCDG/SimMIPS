#ifndef J_TYPE_HPP
#define J_TYPE_HPP

#include "simulated_memory.hpp"
#include "register.hpp"
#include <map>
typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*J_OPCODE)(const uint &, simulated_register&, simulated_memory &);
// input arguments are address(26) AND a reference to the memory block

// J type operators declarations
void J(const uint &address, simulated_register &reg, simulated_memory &mem);
void JAL(const uint &address, simulated_register &reg, simulated_memory &mem);

class J_TYPE // also inherits from memory
{
    public:
    std::map<uchar, J_OPCODE> J_OPCODES;
    J_TYPE();
};

#endif