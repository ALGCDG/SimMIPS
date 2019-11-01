#include "CPU.hpp"
#include <math.h>
#include "register.hpp"

// cannot put functions in map until they are defined
// std::map<uchar, R_OPCODE> CPU::R_OPCODES = {
//     {0, SLL},
//     {2, SRL},
//     {3, SRA},
//     {4, SLLV},
//     {6, SRLV},
//     {7, SRAV},
//     {8, JR},
//     {9, JALR},
//     {12, SYSCALL},
//     {16, MFHI},
//     {17, MTHI},
//     {18, MFLO},
//     {19, MTLO},
//     {24, MULT},
//     {25, MULTU},
//     {26, DIV},
//     {27, DIVU},
//     {32, ADD},
//     {33, ADDU},
//     {34, SUB},
//     {35, SUBU},
//     {36, AND},
//     {37, OR},
//     {38, XOR},
//     {39, NOR},
//     {42, SLT},
//     {43, SLTU}
// };
// std::map<uchar, I_OPCODE> CPU::I =
// {
//     {4, BEQ},
//     {5, BNE},
//     {6, BLEZ},
//     {7, BGTZ},
//     {8, ADDI},
//     {9, ADDIU},
//     {10, SLTI},
//     {11, SLTIU},
//     {12, ANDI},
//     {13, ORI},
//     {14, XORI},
//     {15, LUI},
//     {32, LB},
//     {33, LH},
//     {34, LW},
//     {36, LBU},
//     {37, LHU},
//     {40, SB},
//     {41, SH},
//     {43, SW}
// };
// std::map<uchar, J_OPCODE> CPU::J =
// {
//     // {2, J},
//     // {3, JAL}
// };

// CPU::CPU()
// {
//     std::map<uchar, R_OPCODE> R_OPCODES = {/*
//         {0, SLL},
//         {2, SRL},
//         {3, SRA},
//         {4, SLLV},
//         {6, SRLV},
//         {7, SRAV},
//         {8, JR},
//         {9, JALR},
//         {12, SYSCALL},
//         {16, MFHI},
//         {17, MTHI},
//         {18, MFLO},
//         {19, MTLO},
//         {24, MULT},
//         {25, MULTU},
//         {26, DIV},
//         {27, DIVU},*/
//         {32, ADD}
//         /*,
//         {33, ADDU},
//         {34, SUB},
//         {35, SUBU},
//         {36, AND},
//         {37, OR},
//         {38, XOR},
//         {39, NOR},
//         {42, SLT},
//         {43, SLTU}*/
//     };
// }


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
        (R_OPCODES[pass_funct(instruction)])(rs, rt, rd, shamt, registers, memory);
    }
    else if ((OPCODE >=4 && OPCODE <=15) || (OPCODE >=32 && OPCODE <= 34) || OPCODE == 36 || OPCODE == 37 || OPCODE ==40 || OPCODE ==41 || OPCODE ==43)
    {
        uchar rs, rt;
        uint immediate;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        immediate = pass_immediate(instruction);
        (I_OPCODES[OPCODE])(rs, rt, immediate, registers, memory);
    }
    else if (2 == OPCODE || 3 == OPCODE)
    {
        uint address;
        address = pass_address(instruction);
        (J_OPCODES[OPCODE])(address, registers, memory);
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
        uint instruction;// load instruction
        interpret_instruction(instruction);

    }
    return registers.read_register(2); // return exit code
}

// CPU constructor
CPU::CPU(const std::string &binary_file_path)
{
    memory = new simulated_memory();
    registers = new simulated_register();
    r = new R_TYPE();
    i = new I_TYPE();
    j = new J_TYPE();
}