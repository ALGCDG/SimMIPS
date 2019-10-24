#include "R.hpp"

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