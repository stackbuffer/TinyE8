#include <iostream>
#include "cpu.hpp"

CPU::CPU(){
	std::cout << "Booting up...\n";
}

CPU::~CPU(){

}

void CPU::init(){
	std::cout << "Resetting Registers...\n";

	//reset all the registers, counters, memory, flags
	pc = 0; //set program counter to 0

	//reset registers
	A = 0;
	B = 0;
	IR = 0;

	//reset memory
	for(uint8_t i = 0; i<16; i++){
		memory[i] = 0;
	}

	OUT = 0;
	HALT = false;
}

int CPU::loadProgram(){
	init();

	//load program into memory.
	//in our case, we want to add 7 and 3
	//load 7 at 0110
	//and load 3 at 0111

	memory[0b0000] = 0b00011000; //LDA 1000 or load 7 into A register
	memory[0b0001] = 0b00101001; //ADD 1001 or load 3 into B register, then ADD and store it in A
	memory[0b0010] = 0b11100000; //OUT 0000 or OUTPUT A register contents
	memory[0b0011] = 0b00111011; //SUB 1011 or subtract value stored on memory address 0111
	memory[0b0100] = 0b11100000; //OUT 0000 or OUTPUT A register contents 
	memory[0b0101] = 0b11110000; //HLT 0000 or HALT execution

	//store data in the memory
	memory[0b1000] = 7;
	memory[0b1001] = 3;
	memory[0b1011] = 2;

	return 1;
}


void CPU::execute(){
	//every instruction is 8 bits long
	//higher 4 bits represent instruction
	//and lower 4 bits represent memory address

	//from an 8 bit instruction, Higher 4 bits can be extracted by performing & operation with 0xF0 and right shifting it with 4 bits
	//and Lower 4 bits can be extracted by performing & operation with 0x0F

	//the following code extracts the instruction from the higher 4 bits
	uint8_t opcode = (IR & 0xF0) >> 4;

	switch(opcode){
		//NOP
		case 0b0000:
			break;
		
		//LDA - load contents from lower 4 bits memory address into A register
		case 0b0001:
			A = memory[(IR & 0x0f)];
			break;

		//ADD
		case 0b0010:
			A = A + memory[(IR & 0x0f)];
			break;

		//SUB
		case 0b0011:
			A = A - memory[(IR & 0x0f)];
			break;

		//STA
		case 0b0100:
			memory[(IR&0x0f)] = A;
			break;

		//LDI
		case 0b0101:
			A = IR & 0x0f;
			break;

		//JMP
		case 0b0110:
			//someone verify whether this is true or not.
			pc = pc + (IR & 0x0f);
			break;

		//JC
		case 0b0111:
			//TODO : Implement jump if carry is set
			break;

		//JZ
		case 0b1000:
			//TODO : Implement jump if zero is set
			break;

		//OUT
		case 0b1110:
			OUT = A;
			break;

		//HLT - set HALT flag to true
		case 0b1111:
			HALT = true;
			break;

		default:
			std::cout << "Illegal opcode : " << IR << std::endl;
			exit(0);
	}
}