#include "J.hpp"

// J type operators implementation
void J(const uint &address, simulated_register &reg, simulated_memory &mem)
{
    uint pc_value = mem.get_PC();
    mem.jump_to((pc_value & 0xF0000000) + (address << 2));
}
void JAL(const uint &address, simulated_register &reg, simulated_memory &mem)
{
    uint pc_value = mem.get_PC();
    reg.write_register(31, pc_value + 8);
    mem.jump_to((pc_value & 0xF0000000) + (address << 2));
}

J_TYPE::J_TYPE()
{
    J_OPCODES[2] = J;
    J_OPCODES[3] = JAL;
}
