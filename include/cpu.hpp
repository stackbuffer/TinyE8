#pragma once

/*
 -----------------------------------------------------------------------------------------------
|Instruction set - Each Instruction is 4 bits long and each opcode will be 8 bits or 1 byte long|
 -----------------------------------------------------------------------------------------------
 -------------------------------------------------------------------------------------------------------------------------------
| 0000 - NOP --> No Operation																									|
| 0001 - LDA --> Load contents of a memory address XXXX into A register															|
| 0010 - ADD --> Load contents of a memory address XXXX into B register, then performs A+B and stores the result in A register	|
| 0011 - SUB --> Load contents of a memory address XXXX into B register, then performs A-B and stores the result in A register	|
| 0100 - STA --> Store contents of A register at memory address XXXX															|
| 0101 - LDI --> Load 4 bit immediate value into A register																		|
| 0110 - JMP --> Unconditional jump: sets program counter to XXXX and executes from there										|
| 0111 - JC  --> Jump if carry: sets program counter to XXXX when carry flag is set and executes from there						|
| 1000 - JZ  --> Jump if zero: sets program counter to XXXX when zero flag is set and executes from there						|
| 1110 - OUT --> Output contents of A register to 7 segment display, in our case, we'll print it on console						|
| 1111 - HLT --> Halts the execution																							|
 -------------------------------------------------------------------------------------------------------------------------------

 ---------------------------------
| Example: Add two numbers 7 and 3|
 ---------------------------------
 -----------------------------------------------------------------------------------------------------------
| LDA 0000	;0000 is the memory address of 7 in the RAM. 7 is present at 0000								|
| ADD 0001	;0001 is the memory address 0f 3 in the RAM. 3 is present at 0001								|
| OUT XXXX	;we don't care about XXXX, all we want is whether the last 4 bits are OUT instruction's or not 	|
| HLT XXXX	;similarly, for HLT, we only check the last 4 bits												|
|																											|
| ;In Memory or RAM, the values are stored as follows														|
|																											|
| ;at 0000 we store 7 or in C syntax, we can represent it as memory[0] = 7;									|
| ;similarly at 0001, we store 3, or memory[1] = 3;															|
| ;The output should be 10 																					|
 ----------------------------------------------------------------------------------------------------------- 
 
*/

class CPU{
public:
	uint8_t pc; //Program Counter starts from 0x00

	uint8_t A; 	//A register
	uint8_t B; 	//B register
	uint8_t IR; //Instruction Register

	uint8_t memory[16]; //16 bytes of memory or RAM

	uint16_t OUT; //output

	bool CF; //Carry Flag
	bool ZF; //Zero Flag
	bool HALT; //halt flag

	//constructor and destructor
	CPU();
	~CPU();

	void init(); //initializes the CPU by resetting all the components
	int loadProgram(); //loads a program into the memory[]
	void execute(); // Fetch->Decode->Execute opcode cycle
};
