#include "register.hpp"
#include "simulated_memory.hpp"
#include <map>

typedef unsigned int uint;
typedef unsigned char uchar;

typedef int (*R_OPCODE)(const uchar &, const uchar &, const uchar &, const uchar &, simulated_register &, simulated_memory&);
// input arguments are rs(5), rt(5), rd(5), shamt(5) AND a reference to the register block

// NB I have changed the return type to int for purposes of propagating errors

// R type operators declarations
int SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SRL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SRA(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SLLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SRLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SRAV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int JR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int JALR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SYSCALL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int MFHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int MTHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int MFLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int MTLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int MULT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int MULTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int DIV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int DIVU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int ADD(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int ADDU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SUB(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SUBU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int AND(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int OR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int XOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int NOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SLT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);
int SLTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem);

class R_TYPE
{
    public:
    std::map<uchar, R_OPCODE> R_OPCODES;
    R_TYPE();
};
