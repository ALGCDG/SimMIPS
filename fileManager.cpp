#include "fileManager.hpp"

typedef unsigned int uint;
typedef unsigned char uchar;

fileManager::fileManager(std::string path){
	binary_file.open(path);
}

fileManager::jump_r_w_left_return(int offset){
	int initial_offset = get_currOffset();
	jump_to_offset(offset);
	int num_bytes = 4 - offset%4;

	uint word = 0;

	//uchar * bytes = new char[num_bytes - 1];
	// for(int i = 0; i < num_bytes; i++){
	// 	//bytes[i] = r_byte_advance();
	// 	word |= (r_byte_advance() << (24 - i*4));
	// }

	uchar * bytes = new char[num_bytes - 1];
	binary_file.read(bytes,num_bytes);
	for(int i = 0; i < num_bytes; i++){
		word |= (bytes[i] << (24 - i*8));
	}
	delete bytes;
	jump_to_offset(initial_offset);
	return word;
}

uint fileManager::jump_r_w_right_return(int offset){
	int num_bytes = offset%4 + 1;
	int start_addr = offset - num_bytes + 1;
	int initial_offset = get_currOffset();
	jump_to_offset(start_addr);
	uint word = 0;
	uchar * bytes = new char[num_bytes - 1];
	binary_file.read(bytes, num_bytes);
	for(int i = 0; i < num_bytes; i++){
		word |= (bytes[i] << (num_bytes - i - 1)*8);
	}
	jump_to_offset(initial_offset);
	delete bytes;
	return word;
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

uint fileManager::r_word_maintain(){
	int initial_offset = get_currOffset();
	uint word = r_word_advance();
	binary_file.seekg(initial_offset);
	return word;
}

uint fileManager::jump_r_word_advance(int offset){
	jump_to_offset(offset);
	return r_word_advance();
}

uint fileManager::r_word_advance(){
	//reads a word at the current position
	//file pointer is advanced
	//eg for getting an instruction
	char * buffer = new char[4];
	binary_file.read(buffer,4);
	//returns a significance corrected word, ie: most significant byte highest in the word
	uint word = (uint)buffer[3] | (uint)buffer[2] << 8 | (uint)buffer[1] << 16 | (uint)buffer[0] << 24;
	delete buffer;
	return word;
}

uint fileManager::jump_r_byte_return(int offset){
	//useful for reading just bytes
	int initial_offset = get_currOffset();
	jump_to_offset(offset);
	uchar byte;
	binary_file.read(&byte, 1);
	jump_to_offset(initial_offset); //returns to original offset after read
	return (uint)byte;
}

uint fileManager::r_byte_advance(){
	//useful for half words, and left/right words
	uchar byte;
	binary_file.read(&byte, 1);
	return (uint)byte;
}
