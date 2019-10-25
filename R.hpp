#include "register.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*R_OPCODE)(const uchar &, const uchar &, const uchar &, const uchar &);
// input arguments are rs(5), rt(5), rd(5), shamt(5)

class R_TYPE : public simulated_register
{
    public:
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
};
