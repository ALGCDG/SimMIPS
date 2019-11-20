#include "R.hpp"
#include <climits>
#include <iostream>
// NB, behaviour of shifts, << and >>, is undefined for negative numbers

// R type operators implementations
int SLL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) << shamt);
    return 0;
}
int SRL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) >> shamt);
    return 0;
}
int SRA(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
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
    return 0;
}
int SLLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) << (reg.read_register(rs) % 32));
    return 0;
}
int SRLV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rt) >> (reg.read_register(rs) % 32));
    return 0;
}
int SRAV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    SRA shifts a 32 bit word right be a specified number of bits
    more than this, it must pack the most significant side of the word with
    bits which are the same as the most significant bit in the original word
    */
    uint word = reg.read_register(rt);
    uint shift = reg.read_register(rs) % 32;
    uint shifted_word = word >> shift;
    uint signed_bits = ((word & 0x80000000) > 0) ? 0xFFFFFFFF << (32 - shift) : 0 ;
    reg.write_register(rd, shifted_word | signed_bits);
    return 0;
}
int JR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    mem.jump_to(reg.read_register(rs));
    // std::cerr << "Jumping to address in register " << (int)rs << std::endl; //TESTING 
    // std::cerr << "Jumping to: " << reg.read_register(rs) << std::endl; //TESTING
    return 0;
}
int JALR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, mem.get_PC() + 8);
    mem.jump_to(reg.read_register(rs));
    return 0;
}
int SYSCALL(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem) { return 0;} // I don't believe this is required for coureswork, but WE OUGHT TO CHECK
int MFHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_HI());
    return 0;
}
int MTHI(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_HI(reg.read_register(rs));
    return 0;
}
int MFLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_LO());
    return 0;
}
int MTLO(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_LO(reg.read_register(rs));
    // std::cerr << "LO = " << (uint)(reg.read_LO()) << std::endl; //TESTING
    return 0;
}
int MULT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
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
    return 0;
}
int MULTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
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
    return 0;
}
int DIV(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
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
    return 0;
}
int DIVU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
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
    return 0;
}
int ADD(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    /*
    Given that overflowing behavour of signed datatypes in C++ is undefined
    there is no way we can short cut signed addition and subtraction by using signed ints
    instead we must implement it using unsigned int and detect overflow ourselves
    */
    uint a, b, sum;
    a = reg.read_register(rs);
    b = reg.read_register(rt);
    // checking for ARITHMATIC overflow
    // if (a > INT_MAX - b)
    // {
    //     std::cerr << "ADD arithmatic overflow" << std::endl; // ERROR LOGGING
    //     return -10; // Throwing an arithmatic exception (which will be caught in the CPU execute function)
    // }
    // new overflow check
    sum = a + b;
    if (a < 0x80000000 && b < 0x80000000) // ie a and b positive
    {
        if (sum >= 0x80000000) // ie the sum is negative
        {
            std::cerr << "ADD arithmatic overflow" << std::endl; // ERROR LOGGING
            return -10;
        }

    }
    else if (a >= 0x80000000 && b >= 0x80000000) // ie a and b are negative
    {
        if (sum < 0x80000000) // ie the sum is negative
        {
            std::cerr << "ADD arithmatic overflow" << std::endl; // ERROR LOGGING
            return -10;
        }
    }
    reg.write_register(rd, sum);
    return 0;
}
int ADDU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) + reg.read_register(rt));
    return 0;
}
int SUB(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    uint a, b, difference ;
    a = reg.read_register(rs);
    b = reg.read_register(rt);
    // // checking for overflow
    // // if (a > UINT_MAX - (~b) - 1)
    // bool msb_a = (a & 0x80000000) > 0;
    // bool msb_b = (b & 0x80000000) > 0;
    // uint result = a - b;
    // bool msb_r = (result & 0x80000000) > 0;
    // if (((msb_a&&!msb_b)&&(!msb_r))||((!msb_a&&msb_b)&&(msb_r)))
    // {
    //     std::cerr << "SUB arithmatic overflow" << std::endl; // ERROR LOGGING
    //     return -10;                                          // Throwing an arithmatic exception (which will be caught in the CPU execute function)
    // }
    difference = a - b;
    if (a < 0x80000000 && b >= 0x80000000) // ie a is positive and b is negative
    {
        if (difference >= 0x80000000) // ie the sum is negative
        {
            std::cerr << "SUB arithmatic overflow" << std::endl; // ERROR LOGGING
            return -10;
        }

    }
    else if (a >= 0x80000000 && b < 0x80000000) // ie a is negative and b is positive
    {
        if (difference < 0x80000000) // ie the sum is negative
        {
            std::cerr << "SUB arithmatic overflow" << std::endl; // ERROR LOGGING
            return -10;
        }
    }
    reg.write_register(rd, difference);
    return 0;
}
int SUBU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) - reg.read_register(rt));
    return 0;
}
int AND(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) & reg.read_register(rt));
    return 0;
}
int OR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) | reg.read_register(rt));
    return 0;
}
int XOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, reg.read_register(rs) ^ reg.read_register(rt));
    return 0;
}
int NOR(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, ~(reg.read_register(rs) | reg.read_register(rt)));
    return 0;
}
int SLT(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    // using type casting to signed int
    reg.write_register(rd, ((int)reg.read_register(rs) < (int)reg.read_register(rt))); // we can rely on implicit type conversion of bool to int
    return 0;
}
int SLTU(const uchar &rs, const uchar &rt, const uchar &rd, const uchar &shamt, simulated_register &reg, simulated_memory &mem)
{
    reg.write_register(rd, (reg.read_register(rs) < reg.read_register(rt))); // we can rely on implicit type conversion of bool to int
    return 0;
}

R_TYPE::R_TYPE()
{
    R_OPCODES[0] = SLL;
    R_OPCODES[2] = SRL;
    R_OPCODES[3] = SRA;
    R_OPCODES[4] = SLLV;
    R_OPCODES[6] = SRLV;
    R_OPCODES[7] = SRAV;
    R_OPCODES[8] = JR;
    R_OPCODES[9] = JALR;
    R_OPCODES[12] = SYSCALL;
    R_OPCODES[16] = MFHI;
    R_OPCODES[17] = MTHI;
    R_OPCODES[18] = MFLO;
    R_OPCODES[19] = MTLO;
    R_OPCODES[24] = MULT;
    R_OPCODES[25] = MULTU;
    R_OPCODES[26] = DIV;
    R_OPCODES[27] = DIVU;
    R_OPCODES[32] = ADD;
    R_OPCODES[33] = ADDU;
    R_OPCODES[34] = SUB;
    R_OPCODES[35] = SUBU;
    R_OPCODES[36] = AND;
    R_OPCODES[37] = OR;
    R_OPCODES[38] = XOR;
    R_OPCODES[39] = NOR;
    R_OPCODES[42] = SLT;
    R_OPCODES[43] = SLTU;
}
