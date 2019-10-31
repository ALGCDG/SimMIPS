class simulated_memory{
private:

    static memManager DATA_MEM = memManager();
    static fileManager INSTR_MEM;

    char which_readMemLoc(int location);
    char which_storeMemLoc(int location);
    uint sign_extend_bytes_to_word(uint word, int num_bytes_in);
public:

    simulated_memory(std::string binary_path)

    uint read_byte_u(int base, int offset);//unsigned
    uint read_byte_s(int base, int offset);//signed
    uint read_h_word_u(int base, int offset);//half_word unsigned
    uint read_h_word_s(int base, int offset);//half word signed
    uint read_word(int base, int offset);
    uint read_word_left(int base, int offset);
    uint read_word_right(int base, int offset);

    void store_word(int base, int offset, uint word);
    void store_half_word(int base, int offset, uint half_word);
    void store_byte(int base, int offset, uint byte);

    uint fetch_instruction();
    void jump_to(int address);
    uint get_PC();
    //jump stuff
    //instruction stuff
}
