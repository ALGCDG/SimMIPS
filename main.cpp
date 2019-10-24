// main
#include<string> // for pruposes of passing the binary instruction location
#include <iostream> // for pruposes of passing the binary instruction location

// int main(std::string binary_path)
// {
//     // locate binary
//     // load binary
//     // initialise program counter
//     while (/*program counter does not point to null address*/ true)
//     {
//         // load instruction
//         // increment program counter
//         // execute instruction
//     }
//     return 0;
// }

int main(int argc, char *argv[])    // this is the way it has to be, left over from C
{
    std::string binary_file_name = argv[1];
    std::cerr << argv[1] << std::endl; // how all error should be handled NEVER use cout 
}