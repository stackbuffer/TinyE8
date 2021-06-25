#include <iostream>
#include "cpu.hpp"

int main(int argc, const char *argv[]){
	if(argc != 3){
		std::cout << "Usage : ./main <bin file> <debug>\n\n";
		std::cout << "<bin file> - binary file compiled using eas.py assembler\n";
		std::cout << "<debug> - 1 will print debug info and 0 will omit it\n";
		exit(1);
	}

	int debug = std::stoi(argv[2]);

	CPU cpu; //create the CPU object

	cpu.loadProgram(argv[1]); //load the program into the memory

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

	//Debug output
	if(debug == 1){
		std::cout << " ----------------- \n";
		std::cout << "|      DEBUG      |\n";
		std::cout << " ----------------- \n";
		printf("| PC  : 0x%X       |\n", cpu.pc);
		printf("| A   : 0x%X       |\n", cpu.A);
		printf("| B   : 0x%X       |\n", cpu.B);
		printf("| IR  : 0x%X      |\n", cpu.IR);

		std::cout << "| CF  : " << cpu.CF << "         |\n";
		std::cout << "| ZF  : " << cpu.ZF << "         |\n";
		std::cout << "| OUT : " << cpu.OUT << "         |\n"; 
		std::cout << " ----------------- \n";
	}
	else{
		std::cout << "OUT : " << cpu.OUT << "\n";
	}


	return 0;
}
