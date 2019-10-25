#include "memManager.hpp"

uint memManager::r_word(int offset){
    uint word = DATA[offset] << 12 | DATA[offset+4] << 8 | DATA[offset+8] << 4 | DATA[offset+12];
    return word;
}

uint memManager::r_byte(int offset, bool signed=true){
    uint word = 0;
    uchar byte = DATA[offset];
    word |= byte;
    if((0x8 & byte) && signed){ word | 0xFFF0; }
    return word;
}

uint memManager::r_h_word(int offset, bool signed=true){
    uint word = DATA[offset] << 4 | DATA[offset+4];
    if((0x80 & word) & signed) { word |= 0xFF00; }
    return word;
}


uint memManager::r_word_left(int base, int offset){
    //starting at the start_byte of the word at offset
    //this byte is treated as the most significant byte
    //and as we are loading the left part of the word
    //we need the next most significant byte in the unaligned
    //word
    // -> This means increasing memory address by one byte

    //increase until reaching next alligned address

    uint word_out = 0;
    //increases until encounters next aligned address
    //if initially aligned, will still increase until next aligned
    for(int vADDR = base + offset, shift = 12; vADDR%4 != 0 && shift != 12; vADDR++, shift -= 4){
        uchar temp_byte;
        temp_byte = DATA[vADDR];
        word_out |= temp_byte << shift;
    }
    return word_out;
}

uint memManager::r_word_right(int base, int offset){
    //TODO come back here
    uint word_out = 0;
    int vADDR = base + offset;
    int remainder = vADDR%4;

    for(int i = remainder + 1, shift = 0; i > 0; i--, shift += 4){
        uchar temp_byte;
        temp_byte = DATA[vADDR + i - 1];
        word_out |= temp_byte << shift;
    }
    return word_out;
}

void memManager::s_byte(int offset, uchar byte){
    DATA[offset] = byte;
}

void memManager::s_word(int offset, uint word){
    for(int i = 0; i < 16; i+=4){
        DATA[offset+i/4] = static_cast<uchar>((word & (0xF000 >> i)) >> (12-i));
    }
}
