#include "CPU.hpp"
#include <math.h>

// R type operators
void SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt);
void SRL(const uchar &, const uchar &, const uchar &, const uchar &);
void SRA(const uchar &, const uchar &, const uchar &, const uchar &);
void SLLV(const uchar &, const uchar &, const uchar &, const uchar &);
void SRLV(const uchar &, const uchar &, const uchar &, const uchar &);
void SRAV(const uchar &, const uchar &, const uchar &, const uchar &);
void JR(const uchar &, const uchar &, const uchar &, const uchar &);
void JALR(const uchar &, const uchar &, const uchar &, const uchar &);
void SYSCALL(const uchar &, const uchar &, const uchar &, const uchar &);
void MFHI(const uchar &, const uchar &, const uchar &, const uchar &);
void MTHI(const uchar &, const uchar &, const uchar &, const uchar &);
void MFLO(const uchar &, const uchar &, const uchar &, const uchar &);
void MTLO(const uchar &, const uchar &, const uchar &, const uchar &);
void MULT(const uchar &, const uchar &, const uchar &, const uchar &);
void MULTU(const uchar &, const uchar &, const uchar &, const uchar &);
void DIV(const uchar &, const uchar &, const uchar &, const uchar &);
void DIVU(const uchar &, const uchar &, const uchar &, const uchar &);
void ADD(const uchar &, const uchar &, const uchar &, const uchar &);
void ADDU(const uchar &, const uchar &, const uchar &, const uchar &);
void SUB(const uchar &, const uchar &, const uchar &, const uchar &);
void SUBU(const uchar &, const uchar &, const uchar &, const uchar &);
void AND(const uchar &, const uchar &, const uchar &, const uchar &);
void OR(const uchar &, const uchar &, const uchar &, const uchar &);
void XOR(const uchar &, const uchar &, const uchar &, const uchar &);
void NOR(const uchar &, const uchar &, const uchar &, const uchar &);
void SLT(const uchar &, const uchar &, const uchar &, const uchar &);
void SLTU(const uchar &, const uchar &, const uchar &, const uchar &);

// I type operators
void BEQ(const uchar &, const uchar &, const uint &);
void BNE(const uchar &, const uchar &, const uint &);
void BLEZ(const uchar &, const uchar &, const uint &);
void BGTZ(const uchar &, const uchar &, const uint &);
void ADDI(const uchar &, const uchar &, const uint &);
void ADDIU(const uchar &, const uchar &, const uint &);
void SLTI(const uchar &, const uchar &, const uint &);
void SLTIU(const uchar &, const uchar &, const uint &);
void ANDI(const uchar &, const uchar &, const uint &);
void ORI(const uchar &, const uchar &, const uint &);
void XORI(const uchar &, const uchar &, const uint &);
void LUI(const uchar &, const uchar &, const uint &);
void LB(const uchar &, const uchar &, const uint &);
void LH(const uchar &, const uchar &, const uint &);
void LW(const uchar &, const uchar &, const uint &);
void LBU(const uchar &, const uchar &, const uint &);
void LHU(const uchar &, const uchar &, const uint &);
void SB(const uchar &, const uchar &, const uint &);
void SH(const uchar &, const uchar &, const uint &);
void SW(const uchar &, const uchar &, const uint &);

// J type operators
void J(const uint &address);
void JAL(const uint &address);


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
    {2, J},
    {3, JAL}
};


// functions for interpreting binary instructions
uchar pass_OPCODE(const uint &instruction)
{
    return uint(instruction / pow(2, -26)) & uint(0b111111);
}

uchar pass_funct(const uint &instruction)
{
    /*
    A function specifically for returning the six bit function code of the an R type instruction
    */
    return instruction & 0b111111;
}
uchar pass_rs(const uint &instruction)
{
    return (instruction >> 21) & 0b11111;
}
uchar pass_rt(const uint &instruction)
{
    return (instruction >> 16) & 0b11111;
}
uchar pass_rd(const uint &instruction)
{
    return (instruction >> 11) & 0b11111;
}
uchar pass_shamt(const uint &instruction)
{
    return (instruction >> 6) & 0b11111;
}

uint pass_immediate(const uint &instruction)
{
    return (instruction & 0b1111111111111111);
}
uint pass_address(const uint &instruction)
{
    return (instruction & 0b11111111111111111111111111);
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
        R_OPCODE(pass_funct(instruction))(rs, rt, rd, shamt);
    }
    else if ((OPCODE >=4 && OPCODE <=15) || (OPCODE >=32 && OPCODE <= 34) || OPCODE == 36 || OPCODE == 37 || OPCODE ==40 || OPCODE ==41 || OPCODE ==43)
    {
        uchar rs, rt;
        uint immediate;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        immediate = pass_immediate(instruction);
        J_OPCODE(OPCODE)(rs, rt, immediate);
    }
    else if (2 == OPCODE || 3 == OPCODE)
    {
        uint address;
        address = pass_address(instruction);
        I_OPCODE(OPCODE)(address);
    }
    else
    {
        /*
        ERROR, UNSUPPORTED OPCODE USED, THROW EXCEPTION
        */
    }

}

int run()
{
    // load instruction
    interpret_instruction();
    
}