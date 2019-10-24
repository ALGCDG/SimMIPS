// a header file defining the register class

class simulated_register
{
    // unsure of how to implement program counter
    private:
    static unsigned int general_purpose_registors[32];
    static unsigned int HI, LO;

    public:
    //getters
    static unsigned int read_register(const unsigned char& register_number);
    static unsigned int read_HI();
    static unsigned int read_LO();

    //setters
    static void write_register(const unsigned char& register_number, const unsigned int& value);
    static void write_HI(const unsigned int& value);
    static void write_LO(const unsigned int& value);

    // NB, consider using $ notation
};