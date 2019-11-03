#include "J.hpp"

// J type operators implementation
void J(const uint &address, simulated_register &reg, simulated_memory &mem)
{
}
void JAL(const uint &address, simulated_register &reg, simulated_memory &mem)
{
}

J_TYPE::J_TYPE()
{
    J_OPCODES[2] = J;
    J_OPCODES[3] = JAL;
}