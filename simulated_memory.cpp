//todo
//base + offset not correct. Passing logical address from binary straight
//to the vectors

simulated_memory::simulated_memory(std::string binary_path){
    INSTR_MEM = fileManager(binary_path);
}

uint simulated_memory::sign_extend_bytes_to_word(uint word, int num_bytes_in){
    if((0x10 << (num_bytes_in-1)) & word){
        return ((-1 << num_bytes_in*4) || word);
    }
    else{ return word; }
}

char simulated_memory::which_readMemLoc(int location, int & index){
    //-1 if not valid
    //0 if DATA
    //1 if instr
    //2 if getc
    char returnval = -1;
    if(location < 0x100000000){
        if(location >= 0x10000000 && location <0x10000000 + 0x1000000 ){
            returnval = 1;
            index = location - 0x10000000;
        }
        if(location >= 0x20000000 && location <0x20000000 + 0x4000000){
            returnval = 0;
            index = location - 0x20000000;
        }
        if(location >= 0x30000000 && location <0x30000000 + 0x4){
            returnval = 2;
            index = location - 0x30000000;
        }

    }
    return returnval;
}

char simulated_memory::which_storeMemLoc(int location, int & index){
    //-1 if not valid
    //0 if DATA
    //1 if putc
    char returnval = -1;
    if(location < 0x100000000){
        if(location >= 0x20000000 && location < 0x20000000 + 0x4000000){
            returnval = 0;
            index = location - 0x20000000;
        }
        if(location >= 0x30000004 && location < 0x30000004 + 0x4){
            returnval = 1;
            index = location - 0x30000004;
        }
    }
    return returnval;
}

int conv_to_index()

uint simulated_memory::read_byte_u(int base, int offset){
    int index;
    switch(which_readMemLoc(base+offset, index)){
        case 0:
            return DATA_MEM.read_byte(index, 0);
        case 1:
            return static_cast<uint>(INSTR_MEM.jump_r_byte_return(index));
        case 2:
            //TODO : getc, putc
    }
}

uint simulated_memory::read_byte_s(int base, int offset){
    int index;
    switch(which_readMemLoc(base+offset, index)){
        case 0:
            return DATA_MEM.read_byte(index, 1);
        case 1:
            uint word = (INSTR_MEM.jump_r_byte_return(index));
            word = sign_extend_bytes_to_word(word, 1);
            return word;
        case 2:
            //TODO : getc, putc
    }
}

uint simulated_memory::read_h_word_u(int base, int offset){
    int index;
    switch(which_readMemLoc(base+offset, index){
        case 0:
            return DATA_MEM.r_h_word(index, 0);
        case 1:
            return INSTR_MEM.jump_r_word_return(index) & 0xFFFF;
        case 2:
        //todo
    }
}

uint simulated_memory:read_h_word_s(int base, int offset){
    int index;
    switch(which_readMemLoc(base+offset,index)){
        case 0:
            return DATA_MEM.r_h_word(index, 1);
        case 1:
            return sign_extend_bytes_to_word(INSTR_MEM.jump_r_byte_return(index) & 0xFFFF, 2);
        case 2:
        //todo
    }
}

uint simulated_memory::read_word(int base, int offset){
    int index;
    switch(which_readMemLoc(base+offset,index)){
        case 0:
            return DATA_MEM.r_word(index);
        case 1:
            return INSTR_MEM.jump_r_word_return(index);
        case 2:
        //todo
    }
}

uint simulated_memory::read_word_left(int base, int offset){
    int index;
    switch(which_readMemLoc(base+offset, index)){
        case 0:
            return DATA_MEM.r_word_left(index);
        case 1:
            return INSTR_MEM.jump_r_w_left_return(index);
        case 2:
        //todo
    }
}

uint simulated_memory::read_word_right(int base, int offset){
    int index;
    switch(which_readMemLoc(base+offset, index)){
        case 0:
            return DATA_MEM.r_word_right(index);
        case 1:
            return INSTR_MEM.jump_r_w_right_return(index);
        case 2:
        //todo
    }
}

void simulated_memory::store_word(int base, int offset, uint word){
    int index;
    switch(which_storeMemLoc(base+offset,index)){
        case 0:
            DATA_MEM.s_word(index,word);
            break;
        case 1:
            //todo
    }
}

void simulated_memory::store_half_word(int base, int offset, uint half_word){
    int index;
    switch(which_storeMemLoc(base+offset, index)){
        case 0:
            DATA_MEM.s_h_word(index,half_word);
            break;
        case 1:
            //todo
    }
}

void simulated_memory::store_byte(int base, int offset, uint byte){
    int index;
    switch(which_storeMemLoc(base+offset, index)){
        case 0:
            DATA_MEM.s_byte(index,byte);
            break;
        case 1:
            //todo
    }
}
