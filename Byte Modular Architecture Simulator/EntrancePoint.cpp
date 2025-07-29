#include <iostream>
#include <iomanip>
#include <string>
#include <bitset>
#include "MainMemory.hpp"
#include "RegisterFile.hpp"
#include "CPU.hpp"

uint32_t parseInstruction(const std::string& input) {
    if (input.rfind("0x", 0) == 0) {
        return std::stoul(input, nullptr, 16);
    }
    else if (input.rfind("0b", 0) == 0) {
        return std::bitset<32>(input.substr(2)).to_ulong();
    }
    else {
        throw std::invalid_argument("Invalid input format. Use 0x (hex) or 0b (binary).");
    }
}

int main() {
    MainMemory memory;
    RegisterFile regs;
    CPU cpu(memory, regs);
    cpu.reset();

    std::string input;
    int addr = 0;

    std::cout << "Enter MIPS instructions in hex (e.g., 0x20010001) or binary (e.g., 0b001000...)." << std::endl;
    std::cout << "Type 'run' to execute the instructions.\n\n";

    while (true) {
        std::cout << ">>> ";
        std::getline(std::cin, input);

        if (input == "run") {
            break;
        }

        try {
            uint32_t instruction = parseInstruction(input);
            cpu.loadInstruction(addr, instruction);
            addr += 4;
        }
        catch (const std::exception& e) {
            std::cerr << "Error: " << e.what() << "\n";
        }
    }

    int steps = addr / 4;

    for (int i = 0; i < steps; ++i) {
        cpu.runNextInstruction();
    }

    auto regsState = cpu.getRegisters();
    for (int i = 0; i < 32; ++i) {
        std::cout << "$" << std::setw(2) << std::setfill('0') << i << ": " << regsState[i] << "\n";
    }

    return 0;
}
