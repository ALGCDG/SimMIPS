#include "ioManager.hpp"
#include <iostream>
uint ioManager::read_word()
{
    int input;
    input = std::getchar();
    if(ferror(stdin)){
      std::cerr<< "Error with stdin" << std::endl;
      exit(-21);
    }
    return static_cast<uint>(input);
}

void ioManager::store_word(uint word){
    char out = 0xFF & word;
    std::putchar(out);
    if(ferror(stdin)){
      std::cerr<< "Error with stdin" << std::endl;
      exit(-21);
    }
    return;
}

ioManager::ioManager(){}
