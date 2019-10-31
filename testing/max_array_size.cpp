#include <iostream>
#include <vector>
// a small piece of code to check whether it is feasible to fit the entire address instruction part of memory in an unsigned int array
int main()
{
	std::vector<unsigned int> mem(0x4000000);
	//unsigned int mem[0x4000000];
	std::cout << mem.size() << std::endl;
	for (unsigned int &i : mem)
	{
		i = 0;
	}
	std::cout << "finished zeroing memory" << std::endl;
	return 0; 
}
// testing showed that using a standard array caused a memory segmentation error
// testing with vectors and it appears to work correctly
//
// Out of curiosity I read into why this happens and I found that this is because vectors use heap memory (which there is lots of)
// where as explicitly defined arrays use the stack (which there is little)
