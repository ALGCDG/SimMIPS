uint simulated_memory::sign_extend_bytes_to_word(uint word, int num_bytes_in){
    if((0x10 << (num_bytes_in-1)) & word){
        return ((-1 << num_bytes_in*4) || word);
    }
    else{ return word; }
}

char simulated_memory::which_readMemLoc(int location){
    //-1 if not valid
    //0 if DATA
    //1 if instr
    //2 if getc
    char returnval = -1;
    if(location < 0x100000000){
        if(location >= 0x10000000 && location <0x10000000 + 0x1000000 ){
            returnval = 1;
        }
        if(location >= 0x20000000 && location <0x20000000 + 0x4000000){
            returnval = 0;
        }
        if(location >= 0x30000000 && location <0x30000000 + 0x4){
            returnval = 2;
        }

    }
    return returnval;
}

char simulated_memory::which_storeMemLoc(int location){
    //-1 if not valid
    //0 if DATA
    //1 if putc
    char returnval = -1;
    if(location < 0x100000000){
        if(location >= 0x20000000 && location < 0x20000000 + 0x4000000){
            returnval = 0;
        }
        if(location >= 0x30000004 && location < 0x30000004 + 0x4){
            returnval = 1;
        }
    }
}

uint simulated_memory::read_byte_u(int base, int offset){
    switch(simulated_memory::which_readMemLoc(base+offset)){
        case 0:
            return DATA_MEM.read_byte(base+offset, 0);
        case 1:
            return static_cast<uint>(INSTR_MEM.jump_r_byte_return(offset + base));
        case 2:
            //TODO : getc, putc
    }
}

uint simulated_memory::read_byte_s(int base, int offset){
    switch(simulated_memory::which_readMemLoc(base+offset)){
        case 0:
            return DATA_MEM.read_byte(base+offset, 1);
        case 1:
            uint word = (INSTR_MEM.jump_r_byte_return(offset + base));
            word = simulated_memory::sign_extend_bytes_to_word(word, 1);
            return word;
        case 2:
            //TODO : getc, putc
    }
}

uint simulated_memory::read_h_word_u(int base, int offset){
    switch(simulated_memory::which_readMemLoc(base+offset){
        case 0:
            return DATA_MEM.r_h_word(base+offset, 0);
        case 1:
            return INSTR_MEM.jump_r_word_return(base+offset) & 0xFFFF;
        case 2:
        //todo
    }
}

uint simulated_memory:read_h_word_s(int base, int offset){
    switch(simulated_memory::which_readMemLoc(base+offset)){
        case 0:
            return DATA_MEM.r_h_word(base+offset, 1);
        case 1:
            return sign_extend_bytes_to_word(INSTR_MEM.jump_r_byte_return(base+offset) & 0xFFFF, 2);
        case 2:
        //todo
    }
}

uint simulated_memory::read_word(int base, int offset){
    switch(simulated_memory::which_readMemLoc(base+offset)){
        case 0:
            return DATA_MEM.r_word(base+offset);
        case 1:
            return INSTR_MEM.jump_r_word_return(base+offset);
        case 2:
        //todo
    }
}

uint simulated_memory::read_word_left(int base, int offset){
    
}
