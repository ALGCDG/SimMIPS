#include "register.hpp"
#include "simulated_memory"

typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*R_OPCODE)(const uchar &, const uchar &, const uchar &, const uchar &, simulated_register&);
// input arguments are rs(5), rt(5), rd(5), shamt(5) AND a reference to the register block

class R_TYPE : public simulated_register
{
    public:
    // R type operators declarations
    void SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SRL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SRA(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SLLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SRLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SRAV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void JR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void JALR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SYSCALL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void MFHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void MTHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void MFLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void MTLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void MULT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void MULTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void DIV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void DIVU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void ADD(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void ADDU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SUB(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SUBU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void AND(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void OR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void XOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void NOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SLT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
    void SLTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
};
