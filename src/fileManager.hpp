#ifndef FILEMANAGER_HPP
#define FILEMANAGER_HPP

#include <fstream>
#include <string>
#include <queue>
typedef unsigned int uint;
typedef unsigned char uchar;

class fileManager{
private:
	std::ifstream binary_file;
	bool EOF_FLAG;
public:
	bool get_EOF_FLAG();
	std::queue<uint> instr_buff;
	//TODO update functions
	fileManager(std::string path); //constr
	~fileManager(); //de-constr

	//confusing use of offset:
	//offset in this sense is the logical location (not offset eg base + offset)
	// uint jump_r_w_left_return(int offset); //used
	// uint jump_r_w_right_return(int offset);//used
	// void jump_to_offset(int offset);//used
	// int get_currOffset();//used
	// uint jump_r_word_return(int offset);//used
	// uint r_word_maintain(); //potentially unused
	// uint jump_r_word_advance(int offset);//potentially unused
	// uint r_word_advance();//used
	// uint jump_r_byte_return(int offset);//used
	// uint r_byte_advance(); //potentially unused

	void jump_to_offset(int offset);
	int get_currOffset();
	uint jump_r_word_return(int offset);
	uint r_word_advance();
};
//potentially unused commment means:
//Function created for initial design architecture.
//In current design: not used, extraneous function,
//eg jump read word return uses jump, r_word_advance, then return
// no need for eg r_word_maintain
//

#endif
