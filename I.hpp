#include "register.hpp"
#include "simulated_memory"
typedef unsigned int uint;
typedef unsigned char uchar;

typedef void (*I_OPCODE)(const uchar &, const uchar &, const uint &, simulated_register&, simulated_memory&);
// input arguments are rs(5), rt(5), immediate(16) AND a reference to the register block AND a reference to the memory block

class I_TYPE : public simulated_register
{
    public:
    // I type operators declarations
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
};
