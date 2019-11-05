#include "fileManager.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

fileManager::fileManager(std::string path){
	binary_file.open(path);
}
void fileManager::jump_to_offset(int offset){
	//used just for jumping i.e return to label
	binary_file.seekg(offset);
}
int fileManager::get_currOffset(){
	//gets current file offset
	return binary_file.tellg();
}
uint fileManager::jump_r_word_return(int offset){
	int initial_offset = get_currOffset();
	jump_to_offset(offset);
	uint word = r_word_advance();
	jump_to_offset(initial_offset);
	return word;
}
uint fileManager::r_word_advance(){
	//reads a word at the current position
	//file pointer is advanced
	//eg for getting an instruction
	char * buffer = new char[4];
	binary_file.read(buffer,4);
	//returns a significance corrected word, ie: most significant byte highest in the word
	uint word = (uint)buffer[3] | (uint)buffer[2] << 8 | (uint)buffer[1] << 16 | (uint)buffer[0] << 24;
	delete[] buffer;
	return word;
}
