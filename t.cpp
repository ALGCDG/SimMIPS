#include<map>
#include<string>
#include <iostream>

typedef int (*pfunc)(int);

int ADD(int a);

int ADD(int a)
{
    return a* 2;
}
int main()
{
    // std::map<std::string, pfunc> funcMap; 
    // funcMap["f1"] = f1;

    std::map<std::string, pfunc> funcMap = { {"f1", ADD} };

    // std::cout << funcMap["f1"](2) << std::endl;
    return 0;
}