#include <bitset>
#include <fstream>
#include <string>

class fileManager(){
private:
	std::ifstream binary_file;
public:
	//TODO update functions
	fileManager(std::string path); //constr
	void jump_to_offset(int offset); //sets ifstream to point to offset instruction
	//void increment_offset(); //function for clarity, increments offset 4 bytes
	void goto_next_instr();
	//void set_offset(int offset_in); //sets offset to any number
	std::bitset<32> fetch_instr_next_instr(); //fetches instruction from whatever the filestream is pointing at
}
