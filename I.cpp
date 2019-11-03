#include "I.hpp"

uint sign_extend(uint word, uchar length_of_word)
{
    if ((word & (0b1 << length_of_word)) > 0)
    {
        return (0xFFFFFFFF << length_of_word) | word;
    }
    else 
    {
        return word;
    }
}

// I type operators implementation
int BEQ(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int BNE(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int BLEZ(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int BGTZ(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int ADDI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int ADDIU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, reg.read_register(rs) + sign_extend(immediate, 16));
    return 0;
}
int SLTI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int SLTIU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int ANDI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) 
{
    reg.write_register(rt, reg.read_register(rs) & immediate);
    return 0;
}
int ORI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) 
{
    reg.write_register(rt, reg.read_register(rs) | immediate);
    return 0;
}
int XORI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) 
{
    reg.write_register(rt, reg.read_register(rs) ^ immediate);
    return 0;
}
int LUI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int LB(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int LH(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int LW(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int LBU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int LHU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int SB(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int SH(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}
int SW(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem) {}

I_TYPE::I_TYPE()
{
    I_OPCODES[4] = BEQ;
    I_OPCODES[5] = BNE;
    I_OPCODES[6] = BLEZ;
    I_OPCODES[7] = BGTZ;
    I_OPCODES[8] = ADDI;
    I_OPCODES[9] = ADDIU;
    I_OPCODES[10] = SLTI;
    I_OPCODES[11] = SLTIU;
    I_OPCODES[12] = ANDI;
    I_OPCODES[13] = ORI;
    I_OPCODES[14] = XORI;
    I_OPCODES[15] = LUI;
    I_OPCODES[32] = LB;
    I_OPCODES[33] = LH;
    I_OPCODES[34] = LW;
    I_OPCODES[36] = LBU;
    I_OPCODES[37] = LHU;
    I_OPCODES[40] = SB;
    I_OPCODES[41] = SH;
    I_OPCODES[43] = SW;
}
