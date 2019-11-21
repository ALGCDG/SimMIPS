#include"register.hpp"
#include <iostream> //testing
simulated_register::simulated_register() : general_purpose_registors(32, 0)
{
    //no need to type this many 0s
    //just type
    // std::cerr << "starting registor constructor constructor" << std::endl; // TESTING
    // //unsigned int general_purpose_registors[32] = {0};
    // // general_purpose_registors = {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0};
    // // for (auto &i : general_purpose_registors)
    // // {
    // // 	i = 0;
    // // }
    // // general_purpose_registors = std::vector<unsigned int>(32, 0);
    // for (int i =0 ; i < 32 ; i++){ std::cerr << "Registor " << i << " = " << general_purpose_registors[i] << std::endl; } //TESTING
    // std::cerr << "ending registor constructor constructor" << std::endl; // TESTING
}


//getters
unsigned int simulated_register::read_register(const unsigned char& register_number)
{
    // std::cerr << "reading registor " << (int)register_number << std::endl; //TESTING
    // std::cerr << "$" << (int)register_number << " = " << general_purpose_registors[register_number] << std::endl; //TESTING
    return general_purpose_registors[register_number];
}
unsigned int simulated_register::read_HI()
{
    return HI;
}
unsigned int simulated_register::read_LO()
{
    return LO;
}

//setters
void simulated_register::write_register(const unsigned char& register_number, const unsigned int& value)
{
    // std::cerr << "writing registor " << (int)register_number << std::endl; //TESTING
    // std::cerr << "$" << (int)register_number << " := " << value << std::endl; //TESTING
    // ensure that register $0 is immutable
    if ( register_number > 0 && register_number < 32 )
    {
        general_purpose_registors[register_number] = value;
    }
}
void simulated_register::write_HI(const unsigned int& value)
{
    HI = value;
}
void simulated_register::write_LO(const unsigned int &value)
{
    LO = value;
}

// unsigned int & simulated_register::$(const unsigned char &register_number)
// {
//     // ensure that register $0 is immutable
//     if (register_number > 0 && register_number < 32)
//     {
//         return general_purpose_registors[register_number];
//     }
//     else if (register_number == 0)
//     {
//         return nullptr;
//     }
// }
