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

	//set output register to 0
	OUT = 0;

	//set flags to false
	CF = false;
	ZF = false;
	HALT = false;
}

int CPU::loadProgram(const char *filename){
	init();

	//load program into memory.
	//in our case, we want to add 7 and 3
	//load 7 at 0110
	//and load 3 at 0111

	/*
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
	*/

	//This program will print Triangular numbers until 255
	/*memory[0x0] = 0x1F;
	memory[0x1] = 0x2E;
	memory[0x2] = 0x79;
	memory[0x3] = 0xE0;
	memory[0x4] = 0x4F;
	memory[0x5] = 0x1E;
	memory[0x6] = 0x2D;
	memory[0x7] = 0x4E;
	memory[0x8] = 0x60;
	memory[0x9] = 0x50;
	memory[0xA] = 0x4F;
	memory[0xB] = 0x1D;
	memory[0xC] = 0x4E;
	memory[0xD] = 1;
	memory[0xE] = 1;
	memory[0xF] = 0;*/

	FILE *fp = fopen(filename, "rb");

	if(fp == nullptr){
		std::cout << "File not found!\n";
		exit(0);
	}

	fseek(fp, 0, SEEK_END);          // Jump to the end of the file
	int filesize = ftell(fp);             // Get the current byte offset in the file
	rewind(fp);                      // Jump back to the beginning of the file
	
	uint8_t *buffer = (uint8_t *) malloc((filesize + 1) * sizeof(uint8_t));	
	
	fread(buffer, filesize, 1, fp); // Read in the entire file
	fclose(fp);
	
	for (int i = 0; i < filesize; i++) {
		memory[i] = buffer[i];
	}

	
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
			//set carry flag if addition is overflow. As this is 8 bit, 2^8-1 = 255;
			//when, the addition result is greater than 255, set the carry flag
			CF = (uint16_t(A) + uint16_t(memory[(IR & 0x0f)])) > 255;

			//normal addition
			B = memory[(IR & 0x0f)];
			A = A + B;

			//set zero flag only if A==0
			ZF = A == 0; 
			break;

		//SUB
		case 0b0011:
			//set carry flag if subtraction is overflow, just like in addition
			CF = (uint16_t(A) - uint16_t(memory[(IR & 0x0f)])) > 255;

			//normal subtraction
			B = memory[(IR & 0x0f)];
			A = A - B;

			//set zero flag only if A==0
			ZF = A == 0;
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
			//jump to xxxx instruction and do not increment the PC
			pc = (IR & 0x0f) - 1;
			break;

		//JC
		case 0b0111:
			//jump if carry flag is set
			if(CF){
				pc = (IR & 0x0f) - 1;
			}
			break;

		//JZ
		case 0b1000:
			//jump if zero flag is set
			if(ZF){
				pc = (IR & 0x0f) - 1;
			}
			break;

		//OUT
		case 0b1110:
			OUT = (uint16_t)A;
			std::cout << OUT << "\n";
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
