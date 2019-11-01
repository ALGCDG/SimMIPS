#include "simulated_memory.hpp"
#include "register.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*J_OPCODE)(const uint &, simulated_register&, simulated_memory &);
// input arguments are address(26) AND a reference to the memory block

class J_TYPE // also inherits from memory
{
    public:
    // J type operators declarations
    void J(const uint &address, simulated_register &reg, simulated_memory &mem);
    void JAL(const uint &address, simulated_register &reg, simulated_memory &mem);
};
