#include "CPU.hpp"
#include <math.h>
#include "register.hpp"

// functions for interpreting binary instructions
uchar pass_OPCODE(const uint &instruction)
{
    return (instruction >> 26) & 0b111111;
}

uchar pass_funct(const uint &instruction)
{
    /*
    A function specifically for returning the six bit function code of the an R type instruction
    */
    return instruction & 0x3F;
}
uchar pass_rs(const uint &instruction)
{
    return (instruction >> 21) & 0x1F;
}
uchar pass_rt(const uint &instruction)
{
    return (instruction >> 16) & 0x1F;
}
uchar pass_rd(const uint &instruction)
{
    return (instruction >> 11) & 0x1F;
}
uchar pass_shamt(const uint &instruction)
{
    return (instruction >> 6) & 0x1F;
}

uint pass_immediate(const uint &instruction)
{
    return (instruction & 0xFFFF);
}
uint pass_address(const uint &instruction)
{
    return (instruction & 0x3FFFFFF);
}

void CPU::interpret_instruction(const uint &instruction)
{
    uchar OPCODE = pass_OPCODE(instruction);
    if (0 == OPCODE)
    {
        uchar rs, rt, rd, shamt;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        rd = pass_rd(instruction);
        shamt = pass_shamt(instruction);
        (r.R_OPCODES[pass_funct(instruction)])(rs, rt, rd, shamt, registers, memory);
    }
    else if ((OPCODE >=4 && OPCODE <=15) || (OPCODE >=32 && OPCODE <= 34) || OPCODE == 36 || OPCODE == 37 || OPCODE ==40 || OPCODE ==41 || OPCODE ==43)
    {
        uchar rs, rt;
        uint immediate;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        immediate = pass_immediate(instruction);
        (i.I_OPCODES[OPCODE])(rs, rt, immediate, registers, memory);
    }
    else if (2 == OPCODE || 3 == OPCODE)
    {
        uint address;
        address = pass_address(instruction);
        (j.J_OPCODES[OPCODE])(address, registers, memory);
    }
    else
    {
        /*
        ERROR, UNSUPPORTED OPCODE USED, THROW EXCEPTION
        */
    }

}

int CPU::run()
{
    // while not pointing to null
    for (;;) // i've done some research and I've read this is more efficent than any while loop
    {
        uint instruction = memory.fetch_instruction(); // load instruction
        interpret_instruction(instruction);
    }
    return registers.read_register(2); // return exit code
}

// CPU constructor
CPU::CPU(const std::string &binary_file_path) : memory(binary_file_path), registers(), r(), i(), j()
{
}