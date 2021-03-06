# the make file for the MIPS Simulator and testbench

# finally compiling main
# all: CPU.o MAIN.o
# 	g++ -std=c++11 MAIN.o IO_MEM.o DATA_MEM.o FILE_MEM.o SIM_MEM.o REG.o R.o I.o J.o CPU.o -o /bin/prog

# # compiling linked memory objects
# IO_MEM.o: ioManager.hpp ioManager.cpp
# 	g++ -std=c++11 -c ioManager.cpp
	
# DATA_MEM.o: memManager.hpp memManager.cpp
# 	g++ -std=c++11 -c memManager.cpp

# FILE_MEM.o: fileManager.hpp fileManager.cpp
# 	g++ -std=c++11 -c fileManager.cpp

# SIM_MEM.o: DATA_MEM.o FILE_MEM.o IO_MEM.o
# 	g++ -std=c++11 -c simulated_memory.cpp

# # compiling register class
# REG.o: register.hpp register.cpp
# 	g++ -std=c++11 -c register.cpp

# # compiling instruction set libraries
# R.o: R.hpp R.cpp SIM_MEM.o REG.o
# 	g++ -std=c++11 -c R.cpp

# I.o: I.hpp I.cpp SIM_MEM.o REG.o
# 	g++ -std=c++11 -c I.cpp

# J.o: J.hpp J.cpp SIM_MEM.o REG.o
# 	g++ -std=c++11 -c J.cpp

# # linking all of the above into CPU object
# CPU.o: SIM_MEM.o R.o I.o J.o
# 	g++ -std=c++11 -c CPU.cpp

# # compiling main object file
# MAIN.o: main.cpp CPU.o
# 	g++ -std=c++11 -c main.cpp

.PHONY: assemble

assemble:
	cd mips_testbench ; bash assemble_mips.sh ; bash compile_mips.sh ; cd ..


bin/mips_simulator: ioManager.o fileManager.o memManager.o simulated_memory.o register.o R.o I.o J.o CPU.o main.o
	mkdir -p bin
	g++ -std=c++11 $^ -o bin/mips_simulator
	

simulator: bin/mips_simulator

%.o: src/%.cpp src/%.hpp
	g++ -std=c++11 -c $<

main.o: src/main.cpp
	g++ -std=c++11 -c src/main.cpp

clean:
	rm -f *.o
	rm -f bin/mips_simulator
	rm -f bin/mips_testbench
	cd mips_testbench ; bash assemble_mips_clean.sh ; cd ..
	rm -f test/output/out.csv
	rm -f test/temp/out.csv


testbench: mips_testbench/testbench.sh assemble
	mkdir -p bin
	cp mips_testbench/testbench.sh bin/mips_testbench
	chmod u+x bin/mips_testbench
