#include "memManager.hpp"

//need a getter and a setter
//this way, putchar type class can override the getter and the setter
//whilst reusing the functions

uchar memManager::getDATAbyte(int index){
    return DATA[index];
}

void memManager::setDATAbyte(int index, uchar byte){
    DATA[index] = byte;
}

uint memManager::r_word(int index){
    uint word = getDATAbyte(index) << 24 | getDATAbyte(index+1) << 16 | getDATAbyte(index+2) << 8 | getDATAbyte(index+3);
    return word;
}

uint memManager::r_byte(int index, bool signed=true){
    uint word = 0;
    uchar byte = getDATAbyte(index);
    word |= byte;
    if((0x80 & byte) && signed){ word | 0xFFF0; }
    return word;
}

uint memManager::r_h_word(int index, bool signed=true){
    uint word = getDATAbyte(index) << 8 | getDATAbyte(index+1);
    if((0x8000 & word) & signed) { word |= 0xFFFF0000; }
    return word;
}


uint memManager::r_word_left(int index){
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
    for(int vADDR = index, shift = 24; vADDR%4 != 0 && shift != 24; vADDR++, shift -= 8){
        uchar temp_byte;
        temp_byte = getDATAbyte(vADDR);
        word_out |= temp_byte << shift;
    }
    return word_out;
}

uint memManager::r_word_right(int index){
    //TODO come back here
    uint word_out = 0;
    int vADDR = index;
    int remainder = vADDR%4;

    for(int i = remainder + 1, shift = 0; i > 0; i--, shift += 8){
        uchar temp_byte;
        temp_byte = getDATAbyte(vADDR + i - 1);
        word_out |= temp_byte << shift;
    }
    return word_out;
}

void memManager::s_byte(int index, uint byte){
    byte &= 0x000000FF;
    setDATAbyteDATA(index, static_cast<uchar>(byte));
}

void memManager::s_word(int index, uint word){
    for(int i = 0; i < 32; i+=8){
        setDATAbyte(index+i/8, static_cast<uchar>((word & (0xFF000000 >> i)) >> (24-i)));
    }
}

void memManager::s_h_word(int index, uint h_word){
    uchar b0 = static_cast<uchar>(h_word);
    uchar b1 = static_cast<uchar>(h_word >> 8);

    setDATAbyte(index, b1);
    setDATAbyte(index+1, b0);
}
