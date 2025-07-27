#include <iostream>
#include <iomanip>
#include "MainMemory.hpp"
#include "RegisterFile.hpp"
#include "CPU.hpp"

int main() {
    MainMemory memory;
    RegisterFile regs;
    CPU cpu(memory, regs);

    cpu.reset();

    cpu.loadInstruction(0, 0x20010001); // addi $1, $0, 1
    cpu.loadInstruction(4, 0x20020002); // addi $2, $0, 2
    cpu.loadInstruction(8, 0x00221820); // add  $3, $1, $2

    for (int i = 0; i < 3; ++i) {
        cpu.runNextInstruction();
    }

    auto regsState = cpu.getRegisters();
    for (int i = 0; i < 8; ++i) {
        std::cout << "$" << i << ": " << regsState[i] << std::endl;
    }

    return 0;
}
