#include "CPU.hpp"

// R type operators
void SLL(const uchar &, const uchar &, const uchar &, const uchar &);
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
void J(const uint &);
void JAL(const uint &);


std::map<int, R_OPCODE> CPU::R = 
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
std::map<int, I_OPCODE> CPU::I =
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
std::map<int, J_OPCODE> CPU::J =
{
    {2, J},
    {3, JAL}
};