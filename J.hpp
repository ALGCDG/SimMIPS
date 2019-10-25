#include "register.hpp"
// include memory

typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*J_OPCODE)(const uint &);
// input arguments are address(26)

class J_TYPE // also inherits from memory
{
    public:
    // J type operators declarations
    void J(const uint &address);
    void JAL(const uint &address);
};
