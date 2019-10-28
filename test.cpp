#include <iostream>

int main(){
    int a;
    while(a = std::getchar()){
    //a = std::getchar();
    std::cout << (a == EOF);
    }
}
