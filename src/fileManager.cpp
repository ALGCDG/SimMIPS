#include "fileManager.hpp"
#include <iostream> //TESTING
#include <bitset> //TESTING
typedef unsigned int uint;
typedef unsigned char uchar;

fileManager::fileManager(std::string path){
	std::ifstream binary_file{path};
	//std::cerr << "File name: "<< path << std::endl;
	EOF_FLAG = false;
	instr_loc = 0;
	if(binary_file){
		std::vector<char> tmp_data;
		binary_file.seekg(0, std::ios::end);
		file_length = binary_file.tellg();
		binary_file.seekg(0, std::ios::beg);
		tmp_data.resize(file_length);
		binary_file.read(tmp_data.data(), file_length);
		binary_file.close();
		//file size check - truncates if longer
		//file size measured in bytes
		//max size = 0x1000000 bytes
		file_length = (file_length <= 0x1000000) ? file_length : 0x1000000;
		file_data.resize(file_length);
		for ( int i = 0 ; i < file_length ; i++ )
		{
			file_data[i] = static_cast<uchar>(tmp_data[i]);
		}
	}
	else{
		std::cerr << "Error opening file at path: " << path << std::endl;
		exit(-21);
	}
}
// fileManager::~fileManager()
// {
// 	binary_file.close();
// }

void fileManager::jump_to_offset(int offset){
	//used just for jumping i.e return to label
	// binary_file.seekg(offset);
	instr_loc = offset;
	return;
}
uint fileManager::get_currOffset(){
	//gets current file offset
	// return binary_file.tellg();
	return instr_loc;
}
uint fileManager::jump_r_word_return(int offset){
	//int initial_offset = get_currOffset();
	//jump_to_offset(offset);
	//uint word = r_word_advance();
	//jump_to_offset(initial_offset);
	if(offset > file_length){ return 0; }
	else {
		uint word = (file_data[offset] << 24) | (file_data[offset+1] << 16) | (file_data[offset+2] << 8) | (file_data[offset+3]);
		return word;
	}
}
uint fileManager::r_word_advance(){
	//reads a word at the current position
	//file pointer is advanced
	//eg for getting an instruction
	// char * buffer = new char[4];
	//std::cerr << "current pointer" <<binary_file.tellg() << std::endl;
	// binary_file.read(buffer,4);
	// if(binary_file.eof()){
	// 	std::cerr << "setting EOF" << std::endl; //TESTING
	// 	EOF_FLAG = true;
	// }
	//returns a significance corrected word, ie: most significant byte highest in the word
	// for (int i = 0;i< 4 ; i++){ std::cerr << std::bitset<8>(buffer[i]) << std::endl; }  //TESTING
	//uint word = (uint)buffer[3] + ((uint)buffer[2] << 8) + ((uint)buffer[1] << 16) + ((uint)buffer[0] << 24);
	// uint word = 0;
	// for (int i = 0 ; i < 4 ; i++)
	// {
	// 	word += ((uint)((uchar)(buffer[i]))) << (8 * (3-i));
	// }
	// std::cerr << "Instruction word fetched: "<< std::bitset<32>(word) << std::endl; //testing
	// delete[] buffer;
	if(instr_loc >= file_length){
  	EOF_FLAG = true;
  }
	uint word = (file_data[instr_loc] << 24) | (file_data[instr_loc+1] << 16) | (file_data[instr_loc+2] << 8) | (file_data[instr_loc+3]);
	instr_loc += 4;
	//std::cerr << "Instr word"<< std::hex << word << std::endl;
	return word;
}

bool fileManager::get_EOF_FLAG()
{
	return EOF_FLAG;
}

// TODO: if read past the end of a file, throw memory access exception
