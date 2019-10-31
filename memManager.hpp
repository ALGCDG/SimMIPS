#include <string>
#include <bitset>

typedef unsigned int uint
typedef unsigned char uchar
/*
 - remember, big endian architecture
 - biggest byte is lowest
 - bit order in byte not changed
*/

class memManager(){
private:
	// signed char DATA[0x4000000] = {};
	std::vector<uchar> DATA(0x4000000, 0);
	//maps offset and range to address code
	// std::map<std::tuple<int,int>, std::string> valid_read;
	//maps offset and range to address code
	// std::map<std::tuple<int,int>, std::string> valid_write;
public:
	uint get_char() const;
	//bit extends std::getchar to 32 bits
	void put_char(uint out_char) const;
	//takes raw 32 bit value and writes to command line
	uint r_word(int offset);
	uint r_h_word(int offset, bool signed);
	uint r_byte(int offset, bool signed);
	void w_word(uint word,int offset);
	void w_h_word(std::bitset<16> h_word, int offset);
	void w_byte(uchar byte, int offset);
	//read function
	//write function
	//map for valid ranges, for both read and write
	//
	void interpret_write()
	memManager();
}
