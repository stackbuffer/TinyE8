
# TinyE8 - Ben Eater's 8 Bit CPU Emulator

TinyE8 emulates [Ben Eater's](https://www.youtube.com/channel/UCS0N5baNlQWJCUrhCEo8WlA) 8 bit breadboard CPU. Implemented all the Instructions ~~except `JC` and `JZ`, I need to watch the whole [playlist](https://www.youtube.com/playlist?list=PLowKtXNTBypGqImE405J2565dvjafglHU) before implementing these two instructions.~~.

Here are some screenshots:

![screenshot](https://github.com/0xhh/TinyE8/blob/main/screenshot.png)

![screenshot1](https://github.com/0xhh/TinyE8/blob/main/screenshot1.png)

Source code is extensively commented, so that it is readable.

## Instruction set
```
 -------------------------------------------------------------------------------------------------------------------------------
| 0000 - NOP --> No Operation
| 0001 - LDA --> Load contents of a memory address XXXX into A register
| 0010 - ADD --> Load contents of a memory address XXXX into B register, then performs A+B and stores the result in A register
| 0011 - SUB --> Load contents of a memory address XXXX into B register, then performs A-B and stores the result in A register
| 0100 - STA --> Store contents of A register at memory address XXXX
| 0101 - LDI --> Load 4 bit immediate value into A register
| 0110 - JMP --> Unconditional jump: sets program counter to XXXX and executes from there
| 0111 - JC  --> Jump if carry: sets program counter to XXXX when carry flag is set and executes from there
| 1000 - JZ  --> Jump if zero: sets program counter to XXXX when zero flag is set and executes from there
| 1110 - OUT --> Output contents of A register to 7 segment display, in our case, we'll print it on console
| 1111 - HLT --> Halts the execution
 -------------------------------------------------------------------------------------------------------------------------------
```

In the mean time feel free to fork, implement these instructions and start a pull request. I'll verify changes and merge it to the main branch.

#### Example: Add 7 and 3
```
 -----------------------------------------------------------------------------------------------------------
| LDA 0000	;0000 is the memory address of 7 in the RAM. 7 is present at 0000
| ADD 0001	;0001 is the memory address 0f 3 in the RAM. 3 is present at 0001	
| OUT XXXX	;we don't care about XXXX, all we want is whether the last 4 bits are OUT instruction's or not
| HLT XXXX	;similarly, for HLT, we only check the last 4 bits	
|
| ;In Memory or RAM, the values are stored as follows
|	
| ;at 0000 we store 7 or in C syntax, we can represent it as memory[0] = 7;
| ;similarly at 0001, we store 3, or memory[1] = 3;
| ;The output should be 10
 ----------------------------------------------------------------------------------------------------------- 
```

#### Implemented Instructions:
- [x] NOP
- [x] LDA
- [x] ADD
- [x] SUB
- [x] STA
- [x] LDI
- [x] JMP - ah, fixed it
- [x] JC  - implemented
- [x] JZ  - implemented
- [x] OUT
- [x] HLT

## Loading your own program

#### Loading your own program from `.bin` file
Create .asm file and write your assembly program in it.
The program should contain atleast 16 lines and each line should consist of 1 or 2 instructions

For example: If you want to write a program that adds 7 and 3 and then subtracts 2 from it, it should something like this
```
LDA 8
ADD 9
SUB 10
OUT 0
NOP
NOP
NOP
NOP
7
3
2
NOP
NOP
NOP
NOP
NOP
```

At `line 0`, we can see `LDA 8`, this means that, it loads value from `address 8` into `A register`. This `address 8` is at `line 8` which has a value of `7`. So, it Loads `7` into `A register`.

At `line 1`, we have `ADD 9`, this will store contents from `address 9` into `B register`, then adds this value to contents of `A register`, So, the final value of `A register` will be `10` and `B register` will be `3`.

At `line 2`, we have `SUB 10`, this will store contents from `address 10` int `B register`, then subtracts this value from contents of `A register`, the final value of `A register` will be `8` and `B register` will be `2`

At `line 3`, we have `OUT 0`, this will `OUTPUT` the contents of `A register` on to the console.

Rest of the lines contain `NOP` instructions.

At `line 8`, there is `7`, this value will be used when `line 0` gets executed.
At `line 9`, there is `3`, this value will be used when `line 1` gets executed.
At `line 10`, there is `2`, this value will be used when `line 3` gets executed. 


In this manner, you have to write your assembly program.
And make sure that there are no extra spaces other than spaces between instruction and memory addresses

Once, you write your assembly program, save it. For example, if you have saved it with a name of `add.asm`, then run the following command to generate `.bin` file.

`python3 eas.py add.asm -o add.bin`

This will generate a `.bin` file. You can run this using the emulator with the following command

`./main add.bin 1` where `1` will print the debug info and `0` will omit it.

## Building
Clone the repo using `git clone https://github.com/0xhh/TinyE8.git` and then `cd TinyE8`.

If you are on Linux, make sure you have `g++` working. Then run `sh build.sh` from the terminal.
It will create `main` binary file. Run it using `./main <bin file> <debug = 0 or 1>`.

If you are on Windows, install `C++` compiler using `MinGW` and then run the following command on the `CMD` or `Powershell`

`g++ -c src/*.cpp -std=c++14 -g -Wall -I include && g++ *.o -o ./main.exe <bin file> <debug = 0 or 1>` and then run `main.exe` file from `CMD` or `Powershell`

## TODO
- [x] JC - Implement jump if carry
- [x] JZ - Implement jump if zero
- [x] load program from `.bin` file
- [ ] did I miss something?

## Contributing
Feel free to fork and contribute to this repo. Make sure that your code is readable and add comments wherever they are needed.
