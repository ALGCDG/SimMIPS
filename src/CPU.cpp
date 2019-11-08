#include "CPU.hpp"
#include <math.h>
#include "register.hpp"

// functions for interpreting binary instructions
uchar pass_OPCODE(const uint &instruction)
{
	std::cerr << "OPcode2: " << std::hex << (instruction >> 26) << std::endl; //testing
    return (instruction >> 26) & 0b111111;
}

uchar pass_funct(const uint &instruction)
{
    /*
    A function specifically for returning the six bit function code of the an R type instruction
    */
    return instruction & 0x3F;
}
uchar pass_rs(const uint &instruction)
{
    return (instruction >> 21) & 0x1F;
}
uchar pass_rt(const uint &instruction)
{
    return (instruction >> 16) & 0x1F;
}
uchar pass_rd(const uint &instruction)
{
    return (instruction >> 11) & 0x1F;
}
uchar pass_shamt(const uint &instruction)
{
    return (instruction >> 6) & 0x1F;
}

uint pass_immediate(const uint &instruction)
{
    return (instruction & 0xFFFF);
}
uint pass_address(const uint &instruction)
{
    return (instruction & 0x3FFFFFF);
}

int CPU::interpret_instruction(const uint &instruction)
{
    uchar OPCODE = pass_OPCODE(instruction);
    std::cerr << "OPCODE: " << std::hex << OPCODE << std::endl; //TESTING
    if (0 == OPCODE)
    {
        std::cerr << "R Type" << std::endl; //TESTING
        uchar rs, rt, rd, shamt, funct;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        rd = pass_rd(instruction);
        shamt = pass_shamt(instruction);
        funct = pass_funct(instruction);
        if (r.R_OPCODES.find(funct) == r.R_OPCODES.end()) // Checking to see if function is in the map
        {
            /*
            function map R_OPCODES doesn't contain a function that is associated with that funct value
            invalid instruction, throw exception
            */
            std::cerr << "Invalid instruction: No match for R type with funct " << funct << std::endl; //TESTING
            return -12;
        }
        else
        {
            return (r.R_OPCODES[funct])(rs, rt, rd, shamt, registers, memory);
        }
    }
    else if ((OPCODE >=4 && OPCODE <=15) || (OPCODE >=32 && OPCODE <= 34) || OPCODE == 36 || OPCODE == 37 || OPCODE ==40 || OPCODE ==41 || OPCODE ==43)
    {
        std::cerr << "I Type" << std::endl; //TESTING
        uchar rs, rt;
        uint immediate;
        rs = pass_rs(instruction);
        rt = pass_rt(instruction);
        immediate = pass_immediate(instruction);
        return (i.I_OPCODES[OPCODE])(rs, rt, immediate, registers, memory);
    }
    else if (2 == OPCODE || 3 == OPCODE)
    {
        std::cerr << "J Type" << std::endl; //TESTING
        uint address;
        address = pass_address(instruction);
        (j.J_OPCODES[OPCODE])(address, registers, memory);
        return 0; //returns zero always as J type cannot have arithmetic exceptions
    }
    else
    {
        std::cerr << "Invalid instruction: No match for OPCODE " << std::hex << OPCODE << std::endl; //TESTING
        /*
        ERROR, UNSUPPORTED OPCODE USED, THROW EXCEPTION
        */
        return -12; // invalid instruction return value
    }

}

int CPU::run()
{
    // while not pointing to null
    // for (;;) // i've done some research and I've read this is more efficent than any while loop
    while (!memory.get_program_end_flag()) // i've done some research and I've read this is more efficent than any while loop
    {
        uint instruction = memory.fetch_instruction(); // load instruction
	std::cerr << "fresh from hex" << std::hex << instruction << std::endl; //TESTING
        if (memory.get_exception_flag()) //TODO: implement exception flag
        {
            std::cerr << "ERROR: memory access exception (-11)" << std::endl; //TESTING
            return -11;
        }
        std::cerr << "running instruction: " << instruction << std::endl; //TESTING
        int instruction_status = interpret_instruction(instruction);
        if (instruction_status != 0)
        {
            std::cerr << "ERROR: instruction exception (arithmatic or instruction validity)" << std::endl; //TESTING
            return instruction_status;
        }
    }
    std::cerr << "returning value in register 2" << std::endl; //TESTING
    return registers.read_register(2); // return exit code
}

// CPU constructor
CPU::CPU(const std::string &binary_file_path) : memory(binary_file_path), registers(), r(), i(), j()
{
}
