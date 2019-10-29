#include "register.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*R_OPCODE)(const uchar &, const uchar &, const uchar &, const uchar &, simulated_register&);
// input arguments are rs(5), rt(5), rd(5), shamt(5) AND a reference to the register block

class R_TYPE : public simulated_register
{
    public:
    // R type operators declarations
    void SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SRL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SRA(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SLLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SRLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SRAV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void JR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void JALR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SYSCALL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void MFHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void MTHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void MFLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void MTLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void MULT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void MULTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void DIV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void DIVU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void ADD(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void ADDU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SUB(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SUBU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void AND(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void OR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void XOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void NOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SLT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
    void SLTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg);
};
