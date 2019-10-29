simulated_memory::simulated_memory(std::string binary_path){
    INSTR_MEM = fileManager(binary_path);
}
uint simulated_memory::get_word(int address){
    int word_index;
    char code = which_readMemLoc(address - address%4, word_index);
    switch(code){
        case(0):
            return DATA_MEM.read_word(word_index);
        case(1):
            return INSTR_MEM.read_word(word_index);
        case(2):
            return IO_MEM.read_word();
    }
}
void simulated_memory::put_word(int address, uint word){
    int word_index;
    char code = which_storeMemLoc(address - address%4, word_index);
    switch(code){
        case(0):
            DATA.store_word(word_index, word);
        case(1):
            IO_MEM.store_word(word);
    }
}
char simulated_memory::which_readMemLoc(const int & address, int & word_index){
    //-1 if not valid
    //0 if DATA
    //1 if instr
    //2 if getc
    char returnval = -1;
    if(address < 0x100000000){
        if(address >= 0x10000000 && address < 0x10000000 + 0x1000000){
            returnval = 1;
            word_index = address - 0x10000000;
        }
        if(address >= 0x20000000 && address < 0x20000000 + 0x4000000){
            returnval = 0;
            word_index = address - 0x20000000;
        }
        if(address >= 0x30000000 && address < 0x30000000 + 0x4){
            returnval = 2;
            word_index = address - 0x30000000;
        }
    }
    return returnval;
}
char simulated_memory::which_storeMemLoc(const int & address, int & word_index){
    //-1 if not valid
    //0 if DATA
    //1 if putc
    char returnval = -1;
    if(address < 0x100000000){
        if(address >= 0x20000000 && address < 0x20000000 + 0x4000000){
            returnval = 0;
            word_index = address - 0x20000000;
        }
        if(address >= 0x30000004 && address < 0x30000004 + 0x4){
            returnval = 1;
            word_index = address - 0x30000004;
        }
    }
    return returnval;
}
void simulated_memory::sign_extend_bytes_to_word(uint & word, int num_bytes_in){
    if((0x80 << (num_bytes_in-1)) & word){
        word = ((0xFFFFFFFF << num_bytes_in*4) | word);
    }
}
uint simulated_memory::read_byte_u(int address){
    uint word = get_word(address);
    // word %= (0xFF << address%4);
    word = (word >> (address%4)) & 0xFF;
    return word;
}
uint simulated_memory::read_byte_s(int address){
    uint byte = read_byte_u(address);
    sign_extend_bytes_to_word(byte,1);
    return byte;
}
uint simulated_memory::read_h_word_u(int address){
    uint word = get_word(address);
    ls_2b = address & 0b11;
    if(ls_2b == 0b00){
        return word & 0xFFFF;
    }
    else if(ls_2b == 0b10){
        return ((word & 0xFFFF0000) >> 16);
    }
}
uint simulated_memory:read_h_word_s(int address){
    uint half_word = read_h_word_u(address);
    sign_extend_bytes_to_word(half_word,2);
    return half_word;
}
uint simulated_memory::read_word(int address){
    return get_word(address);
}
uint simulated_memory::read_word_left(int address){
    uint word = get_word(address);
    return word << (address%4)*8;
}
uint simulated_memory::read_word_right(int address){
    uint word = get_word(address);
    return word >> (3-(address%4))*8;
}
void simulated_memory::store_word(int address, uint word){
    put_word(address,word);
}
void simulated_memory::store_half_word(int address, uint word){
    int temp_index; //just to fill the param slot
    if(which_storeMemLoc(address,temp_index) == 1){
        put_word(address, (word & 0xFFFF) << (address & 0b10)*8);
    }
    else{
        uint temp_word = get_word(address);
        temp_word &= (0xFFFF0000 >> (address & 0b10)*8);
        temp_word |= (address << (address & 0b10)*8);
        put_word(address,temp_word);
    }
}
void simulated_memory::store_byte(int address, uint byte){
    int temp_index; //just to fill the param slot
    if(which_storeMemLoc(address,temp_index) == 1){
        put_word(address, (word & 0xFF) << (address & 0b11)*8);
    }
    else{
        uint temp_word = get_word(address);
        temp_word &= ^(0xFF << (address & 0b11)*8); //zero byte
        temp_word |= ((word & 0xFF) << (address & 0b11)*8);
        put_word(address,temp_word);
    }
}

//not changed
