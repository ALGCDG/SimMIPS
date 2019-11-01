# the make file for the MIPS Simulator and testbench

# compiling linked memory objects
IO_MEM.o: ioManager.hpp ioManager.cpp
	g++ -std=c++11 -c ioManager.cpp
	
DATA_MEM.o: memManager.hpp memManager.cpp
	g++ -std=c++11 -c memManager.cpp

FILE_MEM.o: fileManager.hpp fileManager.cpp
	g++ -std=c++11 -c fileManager.cpp

SIM_MEM.o: DATA_MEM.o FILE_MEM.o IO_MEM.o
	g++ -std=c++11 -c simulated_memory.cpp

# compiling instruction set libraries
R.o: R.hpp R.cpp
	g++ -std=c++11 -c R.cpp

I.o: I.hpp I.cpp
	g++ -std=c++11 -c I.cpp

J.o: J.hpp J.cpp
	g++ -std=c++11 -c J.cpp

# linking all of the above into CPU object
CPU.o: SIM_MEM.o R.o I.o J.o
	g++ -std=c++11 -c CPU.cpp

# finally compiling main
all: CPU.o
	g++ -std=c++11 main.cpp -o /bin/prog

clean:
	rm *.o prog
