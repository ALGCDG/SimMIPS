#include "CPU.hpp"
#include <math.h>
#include "register.hpp"

// R type operators declarations
void SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SRL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SRA(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SLLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SRLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SRAV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void JR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void JALR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SYSCALL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MFHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MTHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MFLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MTLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MULT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MULTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void DIV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void DIVU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void ADD(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void ADDU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SUB(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SUBU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void AND(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void OR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void XOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void NOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SLT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SLTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);

// I type operators
void BEQ(const uchar &rs, const uchar &rt, const uint &immediate);
void BNE(const uchar &rs, const uchar &rt, const uint &immediate);
void BLEZ(const uchar &rs, const uchar &rt, const uint &immediate);
void BGTZ(const uchar &rs, const uchar &rt, const uint &immediate);
void ADDI(const uchar &rs, const uchar &rt, const uint &immediate);
void ADDIU(const uchar &rs, const uchar &rt, const uint &immediate);
void SLTI(const uchar &rs, const uchar &rt, const uint &immediate);
void SLTIU(const uchar &rs, const uchar &rt, const uint &immediate);
void ANDI(const uchar &rs, const uchar &rt, const uint &immediate);
void ORI(const uchar &rs, const uchar &rt, const uint &immediate);
void XORI(const uchar &rs, const uchar &rt, const uint &immediate);
void LUI(const uchar &rs, const uchar &rt, const uint &immediate);
void LB(const uchar &rs, const uchar &rt, const uint &immediate);
void LH(const uchar &rs, const uchar &rt, const uint &immediate);
void LW(const uchar &rs, const uchar &rt, const uint &immediate);
void LBU(const uchar &rs, const uchar &rt, const uint &immediate);
void LHU(const uchar &rs, const uchar &rt, const uint &immediate);
void SB(const uchar &rs, const uchar &rt, const uint &immediate);
void SH(const uchar &rs, const uchar &rt, const uint &immediate);
void SW(const uchar &rs, const uchar &rt, const uint &immediate);

// J type operators
void J(const uint &address);
void JAL(const uint &address);

// cannot put functions in map until they are defined
std::map<uchar, R_OPCODE> CPU::R = 
{
    {0, SLL},
    {2, SRL},
    {3, SRA},
    {4, SLLV},
    {6, SRLV},
    {7, SRAV},
    {8, JR},
    {9, JALR},
    {12, SYSCALL},
    {16, MFHI},
    {17, MTHI},
    {18, MFLO},
    {19, MTLO},
    {24, MULT},
    {25, MULTU},
    {26, DIV},
    {27, DIVU},
    {32, ADD},
    {33, ADDU},
    {34, SUB},
    {35, SUBU},
    {36, AND},
    {37, OR},
    {38, XOR},
    {39, NOR},
    {42, SLT},
    {43, SLTU}
};
std::map<uchar, I_OPCODE> CPU::I =
{
    {4, BEQ},
    {5, BNE},
    {6, BLEZ},
    {7, BGTZ},
    {8, ADDI},
    {9, ADDIU},
    {10, SLTI},
    {11, SLTIU},
    {12, ANDI},
    {13, ORI},
    {14, XORI},
    {15, LUI},
    {32, LB},
    {33, LH},
    {34, LW},
    {36, LBU},
    {37, LHU},
    {40, SB},
    {41, SH},
    {43, SW}
};
std::map<uchar, J_OPCODE> CPU::J =
{
    // {2, J},
    // {3, JAL}
};


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

void interpret_instruction(const uint &instruction)
{
    uchar OPCODE = pass_OPCODE(instruction);
    if (0 == OPCODE)
    {
        uchar rs, rt, rd, shamt;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        rd = pass_rd(instruction);
        shamt = pass_shamt(instruction);
        (R_OPCODE(pass_funct(instruction)))(rs, rt, rd, shamt);
    }
    else if ((OPCODE >=4 && OPCODE <=15) || (OPCODE >=32 && OPCODE <= 34) || OPCODE == 36 || OPCODE == 37 || OPCODE ==40 || OPCODE ==41 || OPCODE ==43)
    {
        uchar rs, rt;
        uint immediate;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        immediate = pass_immediate(instruction);
        (I_OPCODE(OPCODE))(rs, rt, immediate);
    }
    else if (2 == OPCODE || 3 == OPCODE)
    {
        uint address;
        address = pass_address(instruction);
        (J_OPCODE(OPCODE))(address);
    }
    else
    {
        /*
        ERROR, UNSUPPORTED OPCODE USED, THROW EXCEPTION
        */
    }

}

// int run()
// {
//     // while not pointing to null
//         // load instruction
//         interpret_instruction();
//     // return exit code
// }

// R type operators implementations
void SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_register(rt) << shamt);
}
void SRL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SRA(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SLLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_register(rt) << read_register(rs));
}
void SRLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SRAV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void JR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void JALR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SYSCALL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MFHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_HI());
}
void MTHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_HI(read_register(rd));
}
void MFLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_LO());
}
void MTLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_LO(read_register(rd));
}
void MULT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void MULTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void DIV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void DIVU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void ADD(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void ADDU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_register(rs) + read_register(rt));
}
void SUB(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SUBU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_register(rs) - read_register(rt));
}
void AND(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_register(rs) & read_register(rt));
}
void OR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_register(rs) | read_register(rt));
}
void XOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, read_register(rs) ^ read_register(rt));
}
void NOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt)
{
    write_register(rd, ~(read_register(rs) | read_register(rt)));
}
void SLT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SLTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);