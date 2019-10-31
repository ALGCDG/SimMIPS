#include <string>
#include "memManager.hpp"
#include "fileManager.hpp"
#include "ioManager.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

class simulated_memory{
private:
    // TODO: I would suggest that this initialisation is done in the constructor
    memManager DATA_MEM = memManager();
    fileManager INSTR_MEM;
    ioManager IO_MEM;

    char which_readMemLoc(int location);
    char which_storeMemLoc(int location);
    uint sign_extend_bytes_to_word(uint word, int num_bytes_in);
public:

    // simulated_memory(std::string binary_path);

    // uint read_byte_u(int base, int offset);//unsigned
    // uint read_byte_s(int base, int offset);//signed
    // uint read_h_word_u(int base, int offset);//half_word unsigned
    // uint read_h_word_s(int base, int offset);//half word signed
    // uint read_word(int base, int offset);
    // uint read_word_left(int base, int offset);
    // uint read_word_right(int base, int offset);

    // void store_word(int base, int offset, uint word);
    // void store_half_word(int base, int offset, uint half_word);
    // void store_byte(int base, int offset, uint byte);

    // uint fetch_instruction();
    // void jump_to(int address);
    // uint get_PC();
    // //jump stuff
    // //instruction stuff

    simulated_memory(std::string binary_path);

    uint get_word(int address);

    void put_word(int address, uint word);

    char which_readMemLoc(const int &address, int &word_index);
 
    char which_storeMemLoc(const int &address, int &word_index);

    void sign_extend_bytes_to_word(uint &word, int num_bytes_in);

    uint read_byte_u(int address);

    uint read_byte_s(int address);

    uint read_h_word_u(int address);

    uint read_h_word_s(int address);

    uint read_word(int address);

    uint read_word_left(int address);

    uint read_word_right(int address);

    void store_word(int address, uint word);

    void store_half_word(int address, uint word);
   
    void store_byte(int address, uint byte);
    

    uint fetch_instruction();
   
    void jump_to(int address);
  
    void get_PC();
  
};
