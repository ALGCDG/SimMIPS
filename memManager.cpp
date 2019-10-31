#include "memManager.hpp"


//need constructor
memManager::memManager()

uint memManager::read_word(int index){
    return (uint)(DATA[index] << 24 | DATA[index+1] << 16 | DATA[index+2] << 8 | DATA[index+3]);
}

void memManager::store_word(int index, uint word){
    for(int i = 0; i < 4; i++){
        DATA[3-i] = (word >> i*8) &= 0xFF;
    }
}
