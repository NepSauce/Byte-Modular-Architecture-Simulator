# MIPS CPU Simulator

A simple MIPS CPU simulator written in C++. It implements instruction fetch, decode, and execute for a subset of the MIPS instruction set.

## Features

- Supports R-type, I-type, and J-type instructions
- 32-bit register file (32 general-purpose registers)
- ALU for arithmetic and logic operations
- Load/store and branching instructions
- Takes instructions in either **hexadecimal** (`0x...`) or **binary** (`0b...`) formats
- Manual instruction loading to memory by address

## Components

- `CPU` — Main processor logic
- `MainMemory` — Simulated byte-addressable memory
- `RegisterFile` — 32 general-purpose registers
- `ALU` — Arithmetic and logic unit
- `ControlUnit` — Generates control signals for each instruction

## Sample Program

### Task: Add 5 and 7, store result in $3

#### Hex format

0x20010005  
0x20020007  
0x00221820


#### Binary format

0b00100000000000010000000000000101
0b00100000000000100000000000000111
0b00000000001000100001100000100000 
