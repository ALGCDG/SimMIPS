#include "simulated_memory.hpp"
#include <iostream> //TESTING

simulated_memory::simulated_memory(std::string binary_path) : INSTR_MEM(binary_path), DATA_MEM(), IO_MEM()
{
    exception_flag = false;
    program_end_flag = false;
    interior_end_flag = false;
}

void simulated_memory::set_exception_flag()
{
    exception_flag = true;
}
bool simulated_memory::get_exception_flag()
{
    return exception_flag;
}
void simulated_memory::set_program_end_flag()
{
    program_end_flag = true;
}
bool simulated_memory::get_program_end_flag()
{
    return program_end_flag;
}

uint simulated_memory::get_word(int address){
    int word_index;
    char code = which_readMemLoc(address, word_index);
    switch(code){
        case(-1):
            return 0;
        case(0):
            return DATA_MEM.read_word(word_index);
        case(1):
            return INSTR_MEM.jump_r_word_return(word_index);
        case(2):
            return IO_MEM.read_word();
    }
    // TODO: function must have a default return here
}
void simulated_memory::put_word(int address, uint word){
    int word_index;
    char code = which_storeMemLoc(address, word_index);
    switch(code){
        case(-1):
            return;
        case(0):
            DATA_MEM.store_word(word_index, word);
	    return;
        case(1):
            IO_MEM.store_word(word);
 	    return;
    }
}
// I suggest we use these instead of literals, from Archie
static const uint INST_BASE = 0x10000000;
static const uint DATA_BASE = 0x20000000;
static const uint GETC_BASE = 0x30000000;
static const uint PUTC_BASE = 0x30000004;

static const uint INST_LEN = 0x1000000;
static const uint DATA_LEN = 0x4000000;
static const uint GETC_LEN = 0x4;
static const uint PUTC_LEN = 0x4;

char simulated_memory::which_readMemLoc(const int & address, int & word_index){
    //takes in any address for the purpose of checking its general validity
    //input address can be unaligned
    //word_index is used exclusively by get_word, it is assured to be alligned
    //the function returns the codes for functions to use


    //-1 if not valid
    //0 if DATA
    //1 if instr
    //2 if getc
    int al_address = address - address%4;
    char returnval = -1;
    // if(address < 0x10000000){
        if(al_address >= INST_BASE && al_address < INST_BASE + INST_LEN){
            returnval = 1;
            word_index = al_address - INST_BASE;
	          std::cerr << "word index: " << word_index << std::endl;
        }
        else if(al_address >= DATA_BASE && al_address < DATA_BASE + DATA_LEN){
            returnval = 0;
            word_index = al_address - DATA_BASE;
        }
        else if(al_address >= GETC_BASE && al_address < GETC_BASE + GETC_LEN){
            returnval = 2;
            word_index = al_address - GETC_BASE;
        }
        else if(al_address == 0){
            returnval = 1;
            word_index = 0;
        }
        else{
            set_exception_flag();
            returnval = -1;
            word_index = 0;
	    std::cerr << "exception flag set by which_readmemloc" << std::endl;
        }
    // }
    return returnval;
}
char simulated_memory::which_storeMemLoc(const int & address, int & word_index){
    //-1 if not valid
    //0 if DATA
    //1 if putc
    char returnval = -1;
    int al_address = address - address%4;
    // if(address < 0x10000000){
        if(al_address >= DATA_BASE && al_address < DATA_BASE + DATA_LEN){
            returnval = 0;
            word_index = al_address - DATA_BASE;
        }
        else if(al_address >= PUTC_BASE && al_address < PUTC_BASE + PUTC_LEN){
            returnval = 1;
            word_index = al_address - PUTC_BASE;
        }
        else{
            set_exception_flag();
            returnval = -1;
            word_index = 0;
	          std::cerr << "mem exception flag set by storememloc" << std::endl;
        }
    // }
    return returnval;
}
void simulated_memory::sign_extend_bytes_to_word(uint & word, int num_bytes_in){
    if((0x80 << (num_bytes_in-1)) & word){
        word = ((0xFFFFFFFF << num_bytes_in*8) | word);
    }
}
uint simulated_memory::read_byte_u(int address){
    uint word = get_word(address);
    //// word %= (0xFF << address%4);
    //word = (word >> (address%4)) & 0xFF;
    //also possibly incorrect logic


    //if address bottom bits : 00, then reading from the most significant byte

    uint byte_offset = address & 0b11;
    uint word_shamt = 8*(3-byte_offset); //how far to shift word right
    					//in order to get the correct byte
					//in the lsB
    uint mask = 0xFF;
    uint word_out = ((word >> word_shamt) & mask);
    return word_out;
}
uint simulated_memory::read_byte_s(int address){
    uint byte = read_byte_u(address);
    sign_extend_bytes_to_word(byte,1);
    return byte;
}
uint simulated_memory::read_h_word_u(int address){
    uint word = get_word(address);
    uint ls_2b = address & 0b11;
    if(ls_2b == 0b00){
        return ((word & 0xFFFF0000) >> 16);
    }
    else if(ls_2b == 0b10){
        return word & 0xFFFF;
    }
    else{
        set_exception_flag();
        return 0;
    }
}
uint simulated_memory::read_h_word_s(int address){
    uint half_word = read_h_word_u(address);
    sign_extend_bytes_to_word(half_word,2);
    return half_word;
}
uint simulated_memory::read_word(int address){
    if((address & 0b11) ^ 0b00){
        set_exception_flag();
        return 0;
    }
    return get_word(address);
}
uint simulated_memory::read_word_left(int address){
    uint word = get_word(address);
    return (word << (address%4)*8);
}
uint simulated_memory::read_word_right(int address){
    uint word = get_word(address);
    return (word >> (3-(address%4))*8);
}
void simulated_memory::store_word(int address, uint word){
    if((address & 0b10) ^ 0b00){
        set_exception_flag();
        return;
    }
    put_word(address,word);
}
void simulated_memory::store_half_word(int address, uint word){
    int temp_index; //just to fill param slot in storememloc
    char returnval = which_storeMemLoc(address, temp_index);
    if(address & 0b1){
        set_exception_flag();
        return;
    }
    if(returnval == 1){
        put_word(address, (word & 0xFFFF) << (address & 0b10)*8);
    }
    else if (returnval == 0){
        uint temp_word = get_word(address);
        //temp_word &= (0xFFFF0000 >> (address & 0b10)*8);
        //temp_word |= (address << (address & 0b10)*8);
        //rewriting for clarity as per

        //if address offset 2, want to edit least sig half word
        //if address offset 0, want to edit most sig half word
        uint h_word = word & 0xFFFF;
        uint mask = ~(0xFFFF0000 >> ((address & 0b10)*8));//mask used to zero correct bits of temp_word

        temp_word &= mask;
        h_word = h_word << (16 - (address & 0b10)*8);//if offset = 2, then dont want to shift
                                                    //if offset = 0, then shift to most sig half word
        temp_word |= h_word;

        put_word(address,temp_word);
    }
}
void simulated_memory::store_byte(int address, uint word){
    int temp_index; //just to fill the param slot
    char returnval = which_storeMemLoc(address,temp_index);
    if(returnval == 1){
        put_word(address, (word & 0xFF) << (address & 0b11)*8);
    }
    else if (returnval == 0){
        //uint temp_word = get_word(address);
        //temp_word &= ~(0xFF000000 >> (address & 0b11)*8); //zero byte
        //temp_word |= ((word & 0xFF) << (address & 0b11) * 8);
        //std::cerr << "temp word " << temp_word << std::endl;

	//rewriting for clarity - current code bug prone and opaque
	uint temp_word = get_word(address);
	uint byte_offset = address & 0b11;
	uint bottom_byte = word & 0xFF;
	//if the byte offset is 0, need to shift to highest char
	//if the byte offset is 3, keep at lowest char
	uint mask_shamt = (8*(3-byte_offset));
	temp_word = (temp_word & ~(0xFF << mask_shamt)) | (bottom_byte << mask_shamt);

	put_word(address,temp_word);
    }
    else { return; }
}

uint simulated_memory::fetch_instruction(){
    if(!INSTR_MEM.instr_buff.empty()){
        uint instruction = INSTR_MEM.instr_buff.front();
        INSTR_MEM.instr_buff.pop();
        if(interior_end_flag){ set_program_end_flag(); }
        //std::cerr << "Getting instruction from queue" << std::endl;//TESTING
        return instruction;
    }
    else{
        // return INSTR_MEM.r_word_advance();
        uint instr = INSTR_MEM.r_word_advance();
        //std::cerr << "Getting instruction from file" << std::endl;//TESTING
        if(!INSTR_MEM.get_EOF_FLAG()){
            //std::cerr << "Not at EOF" << std::endl; //TESTING
            return instr;
        }
        else
        {
            std::cerr << "EOF, exception flag set" << std::endl;//TESTING
            set_exception_flag();
	    std::cerr << "Current PC: "<< std::hex << get_PC() - 0x10000000 << std::endl;//TESTING
            return 0;
        }
    }
}
void simulated_memory::jump_to(int address){
    int word_index;
    std::cerr << "jumping to address: " << address << std::endl;//TESTING
    char returnval = which_readMemLoc(address, word_index);
    if((returnval != 1) || (address & 0b11 != 0)){
	std::cerr << "Illegal jump address" << std::endl; // TESTING
        set_exception_flag();
    }
    if (address == 0)
    {
        // handles program termination
        interior_end_flag = true;
        std::cerr << "interior end flag set" << std::endl; //Testing
    }
    //check returnval
    INSTR_MEM.instr_buff.push(fetch_instruction());
    //std::cerr << "pushing to queue, queue size: " << INSTR_MEM.instr_buff.size() << std::endl; //Testing
    INSTR_MEM.jump_to_offset(word_index);
}
uint simulated_memory::get_PC(){
    return INSTR_MEM.get_currOffset() + INST_BASE; // must be memory address (not relative instruction address)
    // NB consider writing all these memory addresses as constant unsigned ints, code with large literals are hard to read
}
