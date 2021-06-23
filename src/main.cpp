#include <iostream>
#include "cpu.hpp"

int main(int argc, const char *argv[]){

	CPU cpu; //create the CPU object

	cpu.loadProgram(); //load the program into the memory

	//execute until HALT flag is set to true
	while(!cpu.HALT){
		//fetch instruction using the program counter from memory
		//into the instruction register IR
		cpu.IR = cpu.memory[cpu.pc];

		//execute the instruction
		cpu.execute();
		//increment the program counter by 1
		cpu.pc += 0b0001;
	}

	std::cout << "OUT : " << cpu.OUT << "\n";

	return 0;
}