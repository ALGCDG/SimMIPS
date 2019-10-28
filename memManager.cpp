#include "memManager.hpp"

uint memManager::r_word(int offset){
    uint word = DATA[offset] << 24| DATA[offset+4] << 16 | DATA[offset+8] << 8 | DATA[offset+12];
    return word;
}

uint memManager::r_byte(int offset, bool signed=true){
    uint word = 0;
    uchar byte = DATA[offset];
    word |= byte;
    if((0x80 & byte) && signed){ word | 0xFFF0; }
    return word;
}

uint memManager::r_h_word(int offset, bool signed=true){
    uint word = DATA[offset] << 8 | DATA[offset+1];
    if((0x8000 & word) & signed) { word |= 0xFFFF0000; }
    return word;
}


uint memManager::r_word_left(int offset){
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
    for(int vADDR = offset, shift = 24; vADDR%4 != 0 && shift != 24; vADDR++, shift -= 8){
        uchar temp_byte;
        temp_byte = DATA[vADDR];
        word_out |= temp_byte << shift;
    }
    return word_out;
}

uint memManager::r_word_right(int offset){
    //TODO come back here
    uint word_out = 0;
    int vADDR = offset;
    int remainder = vADDR%4;

    for(int i = remainder + 1, shift = 0; i > 0; i--, shift += 8){
        uchar temp_byte;
        temp_byte = DATA[vADDR + i - 1];
        word_out |= temp_byte << shift;
    }
    return word_out;
}

void memManager::s_byte(int offset, uint byte){
    byte &= 0x000000FF;
    DATA[offset] = static_cast<uchar>(byte);
}

void memManager::s_word(int offset, uint word){
    for(int i = 0; i < 32; i+=8){
        DATA[offset+i/8] = static_cast<uchar>((word & (0xFF000000 >> i)) >> (24-i));
    }
}

void memManager::s_h_word(int offset, uint h_word){
    uchar b0 = static_cast<uchar>(h_word);
    uchar b1 = static_cast<uchar>(h_word >> 8);

    DATA[offset] = b1;
    DATA[offset+1] = b0;
}
