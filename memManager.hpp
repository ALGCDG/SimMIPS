#include <string>
#include <vector>
#include <bitset>

typedef unsigned int uint;
typedef unsigned char uchar;
/*
 - remember, big endian architecture
 - biggest byte is lowest
 - bit order in byte not changed
*/

class memManager{
private:
	// signed char DATA[0x4000000] = {};
	std::vector<uchar> DATA(0x4000000, 0);
	//maps offset and range to address code
	// std::map<std::tuple<int,int>, std::string> valid_read;
	//maps offset and range to address code
	// std::map<std::tuple<int,int>, std::string> valid_write;
public:
	uint read_word(int index);
	void store_word(int index, uint word);
	memManager();
};
