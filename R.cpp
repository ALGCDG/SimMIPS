#include "R.hpp"
#include <climits>
#include <iostream>
// NB, behaviour of shifts, << and >>, is undefined for negative numbers

// R type operators implementations
void R_TYPE::SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) << shamt);
}
void R_TYPE::SRL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) >> shamt);
}
void R_TYPE::SRA(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    SRA shifts a 32 bit word right be a specified number of bits
    more than this, it must pack the most significant side of the word with
    bits which are the same as the most significant bit in the original word
    */
    uint word = reg.read_register(rt);
    uint shifted_word = word >> shamt;
    uint signed_bits = ((word & 0x80000000) > 0) ? 0xFFFFFFFF << (32 - shamt) : 0 ;
    reg.write_register(rd, shifted_word | signed_bits);
}
void R_TYPE::SLLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) << reg.read_register(rs));
}
void R_TYPE::SRLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) >> reg.read_register(rs));
}
void R_TYPE::SRAV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    SRA shifts a 32 bit word right be a specified number of bits
    more than this, it must pack the most significant side of the word with
    bits which are the same as the most significant bit in the original word
    */
    uint word = reg.read_register(rt);
    uint shift = reg.read_register(rs);
    uint shifted_word = word >> shift;
    uint signed_bits = ((word & 0x80000000) > 0) ? 0xFFFFFFFF << (32 - shift) : 0 ;
    reg.write_register(rd, shifted_word | signed_bits);
}
void R_TYPE::JR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem) {}
void R_TYPE::JALR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem) {}
// void R_TYPE::SYSCALL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem) {} // I don't believe this is required for coureswork, but WE OUGHT TO CHECK
void R_TYPE::MFHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_HI());
}
void R_TYPE::MTHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_HI(reg.read_register(rd));
}
void R_TYPE::MFLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_LO());
}
void R_TYPE::MTLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_LO(reg.read_register(rd));
}
void R_TYPE::MULT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    MULT does signed multiplication of two 32 bit words
    The result, a 64 bit word, is stored in two parts
    The most significant "top" half in HI
    and the least significant "bottom" half in LO

    this simplest way to do this 
    */
    unsigned long long int product = (long long int) reg.read_register(rt) * reg.read_register(rs); // by casting the first argument, we ensure that it is a long long int (64 bit) operation
    // conversion from signed long long int to unsigned long long int should be implicitly handled
    reg.write_HI((product & 0xFFFFFFFF00000000) >> 32 );
    reg.write_LO(product & 0x00000000FFFFFFFF);
}
void R_TYPE::MULTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    MULTU does unsigned multiplication of two 32 bit words
    The result, a 64 bit word, is stored in two parts
    The most significant "top" half in HI
    and the least significant "bottom" half in LO
    */
    unsigned long long int product = (unsigned long long int) reg.read_register(rt) * reg.read_register(rs); // by casting the first argument, we ensure that it is a long long int (64 bit) operation
    reg.write_HI((product & 0xFFFFFFFF00000000) >> 32 );
    reg.write_LO(product & 0x00000000FFFFFFFF);
}
void R_TYPE::DIV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    DIV does signed division of two 32 bit words
    the result is made up of two parts, the quotient and the remainder
    the quotient is stored in LO
    the remainder is stored in HI

    this represents quite a problem as the behaviour of the modulo operator (%)
    is poorly defined for when the arguments are not both positive

    MIPS specifies that dividend and remainer must have same sign
    */
    reg.write_LO((int) reg.read_register(rs) / reg.read_register(rt));
    reg.write_HI((int) reg.read_register(rs) % reg.read_register(rt));
}
void R_TYPE::DIVU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    DIVU does unsigned division of two 32 bit words
    the result is made up of two parts, the quotient and the remainder
    the quotient is stored in LO
    the remainder is stored in HI

    there is an issue about what happens if the number in register rt is zero - unclear
    */
    reg.write_LO(reg.read_register(rs) / reg.read_register(rt));
    reg.write_HI(reg.read_register(rs) % reg.read_register(rt));
}
void R_TYPE::ADD(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    Given that overflowing behavour of signed datatypes in C++ is undefined
    there is no way we can short cut signed addition and subtraction by using signed ints
    instead we must implement it using unsigned int and detect overflow ourselves
    */
    uint a, b;
    a = reg.read_register(rs);
    b = reg.read_register(rt);
    // checking for ARITHMATIC overflow
    if (a > INT_MAX - b)
    {
        std::cerr << "ADD arithmatic overflow" << std::endl; // ERROR LOGGING
        throw(-10); // Throwing an arithmatic exception (which will be caught in the CPU execute function)
        // in the event of overflow, the register write will not occur
    }
    reg.write_register(rd, a + b);
}
void R_TYPE::ADDU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) + reg.read_register(rt));
}
void R_TYPE::SUB(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    uint a, b;
    a = reg.read_register(rs);
    b = reg.read_register(rt);
    // checking for overflow
    // if (a > UINT_MAX - (~b) - 1)
    bool msb_a = a & 0x80000000 > 0;
    bool msb_b = b & 0x80000000 > 0;
    uint result = a - b;
    bool msb_r = result & 0x80000000 > 0;
    if ((msb_a&&!msb_b)&&(!msb_r))||((!msb_a&&msb_b)&&(msb_r))
    {
        std::cerr << "SUB arithmatic overflow" << std::endl; // ERROR LOGGING
        throw(-10);                                          // Throwing an arithmatic exception (which will be caught in the CPU execute function)
        // in the event of overflow, the register write will not occur
    }
    reg.write_register(rd, result);
}
void R_TYPE::SUBU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) - reg.read_register(rt));
}
void R_TYPE::AND(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) & reg.read_register(rt));
}
void R_TYPE::OR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) | reg.read_register(rt));
}
void R_TYPE::XOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) ^ reg.read_register(rt));
}
void R_TYPE::NOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, ~(reg.read_register(rs) | reg.read_register(rt)));
}
void R_TYPE::SLT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    // using type casting to signed int
    reg.write_register(rd, ((int) reg.read_register(rs) < reg.read_register(rt))); // we can rely on implicit type conversion of bool to int
}
void R_TYPE::SLTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, (reg.read_register(rs) < reg.read_register(rt))); // we can rely on implicit type conversion of bool to int
}