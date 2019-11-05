#include "ioManager.hpp"
#include <iostream>
uint ioManager::read_word()
{
    int input;
    input = std::getchar();
    return static_cast<uint>(input);
}

void ioManager::store_word(uint word){
    char out = 0xFF & word;
    std::putchar(out);
    return;
}

ioManager::ioManager(){}
