
# TinyE8 - Ben Eater's 8 Bit CPU Emulator

TinyE8 emulates [Ben Eater's](https://www.youtube.com/channel/UCS0N5baNlQWJCUrhCEo8WlA) 8 bit breadboard CPU. Implemented all the Instructions except `JC` and `JZ`, I need to watch the whole [playlist](https://www.youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU) before implementing these two instructions.

Source code is extensively commented, so that it is readable.

## Instruction set
```
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
```

In the mean time feel free to fork, implement these instructions and start a pull request. I'll verify changes and merge it to the main branch.

#### Example: Add 7 and 3
```
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
```

#### Implemented Instructions:
- [x] NOP
- [x] LDA
- [x] ADD
- [x] SUB
- [x] STA
- [x] LDI
- [x] JMP - this would backstab me
- [ ] JC
- [ ] JZ
- [x] OUT
- [x] HLT

## Loading your own program
Go to `src/cpu.cpp` file and from `line 40` add your own program as mentioned in the above example. At first site, it seems confusing but once you do it on your own, it will be a piece of cake. I will explain it in simpler words. We have `memory or RAM` of size `16 bytes`, we'll load our program from `0b0000` to `0b1111`.

For example:

Loading a program that adds 7 and 3 would be as follows
```
LDA 1000
ADD 1001
OUT 0000

;at address 1000, we'll store 7
;and at address 1001, we'll store 3
```
In `src/cpu.cpp`, you should write the code as follows
```
memory[0b0000] = 0b00011000; //LDA 1000 or load 7 into A register from memory[0b1000] or memory[8]
memory[0b0001] = 0b00101001; //ADD 1001 or load 3 into B register, then ADD and store it in A
memory[0b0010] = 0b11100000; //OUT 0000 or OUTPUT A register contents

//store data in the memory
memory[0b1000] = 7; //store 7 at memory[8], so that we can access it using LDA instruction
memory[0b1001] = 3; //store 3 at memory[9], so that we can access it using ADD instruction
```
I hope you understand it.

## TODO
- [ ] JC - Implement jump if carry
- [ ] JZ - Implement jump if zero
- [ ] load program from `.bin` file
- [ ] did I miss something?

## Contributing
Feel free to fork and contribute to this repo. Make sure that your code is readable and add comments wherever they are needed.
