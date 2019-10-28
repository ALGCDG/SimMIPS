// a header file declaring the Program Counter ( a special kind of register )

class program_counter
{
    private:
    unsigned int value;

    public:
    void operator++();
    void operator+=(const int& jump_distance);
    void operator--();
    void operator-=(const int& jump_distance);
    unsigned int get_count();
    program_counter();
};