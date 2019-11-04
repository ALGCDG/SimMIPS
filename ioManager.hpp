//inclusion guard
#ifndef IOMANAGER_HPP
#define IOMANAGER_HPP

typedef unsigned int uint;
typedef unsigned char uchar;
class ioManager
{
    public:
    uint read_word();
    void store_word(uint word);
    ioManager();

};

#endif