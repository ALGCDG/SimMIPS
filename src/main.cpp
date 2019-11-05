// main
#include <string> // for pruposes of passing the binary instruction location
#include <iostream> // for pruposes of passing the binary instruction location and error messages
#include "CPU.hpp" // main implementation of the simulated CPU

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
    std::string binary_file_name = argv[1]; // 
    // std::cerr << argv[1] << std::endl; // how all error should be handled NEVER use cout 
    CPU processor(binary_file_name);// constructing the simulated processor
    return processor.run(); // runs the processor, the run function returns the value of the register 2


    exit(-2); // how we should exit in event of error
    // UMMMMM, ACTUALLY, WE SHOULDN'T, CAUSES MEMORY LEEKS CAUSE DECONSTRUCTORS ARE NOT CALLED
    // to retrieve the exit value, use "echo $?"
    std::cerr << "helo" << std::endl;
}