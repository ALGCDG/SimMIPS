#include"register.hpp"

simulated_register::simulated_register()
{
    //no need to type this many 0s
    //just type
    //unsigned int general_purpose_registors[32] = {0};
    unsigned int general_purpose_registors[32] = {
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0,
        0};
}


//getters
unsigned int simulated_register::read_register(const unsigned char& register_number)
{
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
