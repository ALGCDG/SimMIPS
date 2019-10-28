#include"program_counter.hpp"

void program_counter::operator+=(const int &jump_distance)
{
    value += jump_distance * 4;
}
void program_counter::operator-=(const int &jump_distance)
{
    value -= jump_distance * 4;
}
void program_counter::operator++()
{
    value += 4;
}
void program_counter::operator--()
{
    value -= 4;
}
unsigned int program_counter::get_count()
{
    return value;
}
program_counter::program_counter()
{
    value = 0;
}