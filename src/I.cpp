#include "I.hpp"
#include <iostream> //TESTING
uint sign_extend(uint word, uchar length_of_word)
{
    if ((word & (0b1 << (length_of_word - 1))) > 0)
    {
        return (0xFFFFFFFF << length_of_word) | word;
    }
    else
    {
        return word;
    }
}

// I type operators implementation
int BEQ(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem){
    if(reg.read_register(rs) == reg.read_register(rt)){
        mem.jump_to(mem.get_PC() + sign_extend(immediate << 2, 18));
    }
    return 0;
}
int BNE(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem){
    if(reg.read_register(rs) != reg.read_register(rt)) {
	std::cerr << "PC before BNE: " << mem.get_PC() << std::endl;
	std::cerr << "BNE immediate: " << immediate << std::endl;
	std::cerr << "PC during BNE: " << mem.get_PC() + sign_extend(immediate << 2, 18) << std::endl;
        mem.jump_to(mem.get_PC() + sign_extend(immediate << 2, 18));
    }
    return 0;
}
int BLEZ(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem){
    if(static_cast<int>(reg.read_register(rs)) <= 0){
        mem.jump_to(mem.get_PC() + sign_extend(immediate << 2, 18));
    }
    return 0;
}
int BGTZ(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem){
    if(static_cast<int>(reg.read_register(rs)) > 0){
        mem.jump_to(mem.get_PC() + sign_extend(immediate << 2, 18));
    }
    return 0;
}
int ADDI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    //overflow possible
    uint a = reg.read_register(rs);
    uint b = sign_extend(immediate, 16);
    uint sum = a + b;
    // !(a^b) Top bit true if they are the same
    // (a^sum) Top bit true if sign change
    // !(a^b) & (a^sum) & 0x80000000
    if( !(a^b) & (a^sum) & 0x80000000 ){ //then possible overflow
        return -12;
    }
    reg.write_register(rt, sum);
    return 0;
}
int ADDIU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, reg.read_register(rs) + sign_extend(immediate, 16));
    return 0;
}
int SLTI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, static_cast<int>(reg.read_register(rs)) < static_cast<int>(sign_extend(immediate,16)));
    return 0;
}
int SLTIU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, reg.read_register(rs) < sign_extend(immediate,16));
    return 0;
}
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
int LUI(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, immediate << 16);
    return 0;
}
int LB(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt,mem.read_byte_s(reg.read_register(rs) + sign_extend(immediate,16)));
    return 0;
}
int LH(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, mem.read_h_word_s(reg.read_register(rs) + sign_extend(immediate,16)));
    return 0;
}
int LW(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, mem.read_word(reg.read_register(rs) + sign_extend(immediate,16)));
    return 0;
}
int LBU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt,mem.read_byte_u(reg.read_register(rs) + sign_extend(immediate,16)));
    return 0;
}
int LHU(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rt, mem.read_h_word_u(reg.read_register(rs) + sign_extend(immediate,16)));
    return 0;
}
int SB(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    mem.store_byte(reg.read_register(rs) + sign_extend(immediate,16), reg.read_register(rt));
    return 0;
}
int SH(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    mem.store_half_word(reg.read_register(rs) + sign_extend(immediate,16), reg.read_register(rt));
    return 0;
}
int SW(const uchar &rs, const uchar &rt, const uint &immediate, simulated_register &reg, simulated_memory &mem)
{
    mem.store_word(reg.read_register(rs) + sign_extend(immediate,16), reg.read_register(rt));
    return 0;
}

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
    I_OPCODES[35] = LW;
    I_OPCODES[36] = LBU;
    I_OPCODES[37] = LHU;
    I_OPCODES[40] = SB;
    I_OPCODES[41] = SH;
    I_OPCODES[43] = SW;
}
