#include "memManager.hpp"
#include <iostream>

//need constructor
memManager::memManager() : DATA(0x4000000, 0)
{
    // DATA = std::vector<uchar>(0x4000000, 0);
}

uint memManager::read_word(int index){
    return (uint)(DATA[index] << 24 | DATA[index+1] << 16 | DATA[index+2] << 8 | DATA[index+3]);
}

void memManager::store_word(int index, uint word){
    // std::cerr << "Word stored: " << std::hex << word << std::endl;
    for(int i = 0; i < 4; i++){
        DATA[3-i+index] = (word >> i*8) & 0xFF;
    }
    //std::cerr << "Word at word alligned address written to: ";
    //std::cerr << std::hex << DATA[index] + (DATA[index+1] << 8) + (DATA[index+2] << 16) + (DATA[index+3] << 24) << std::endl;
 }
