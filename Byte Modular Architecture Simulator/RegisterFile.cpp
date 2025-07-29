#include "RegisterFile.hpp"

/*
MIPS Register Index Reference:
 0: $zero       - Always 0
 1: $at         - Assembler temporary
 2-3: $v0-$v1   - Function return values
 4-7: $a0-$a3   - Function arguments
 8-15: $t0-$t7  - Temporaries
 16-23: $s0-$s7 - Saved temporaries
 24-25: $t8-$t9 - More temporaries
 26-27: $k0-$k1 - Kernel reserved
 28: $gp        - Global pointer
 29: $sp        - Stack pointer
 30: $fp        - Frame pointer
 31: $ra        - Return address
*/

RegisterFile::RegisterFile() {
    resetAllReg();
}

uint32_t RegisterFile::readReg(uint8_t addr) const {
    if (addr == 0) {
        return 0;
    }

    if (addr < 32) {
        return registers[addr];
    }

    return 0; 
}

void RegisterFile::writeReg(uint8_t index, uint32_t set) {
    if (index == 0) {
        return;
    }

    if (index < 32) {
        registers[index] = set;
    }
}

void RegisterFile::resetAllReg() {
    for (int i = 0; i < 32; ++i) {
        registers[i] = 0;
    }
}

std::array<uint32_t, 32> RegisterFile::getAllRegisters() const {
    std::array<uint32_t, 32> regs{};
    for (int i = 0; i < 32; ++i) {
        regs[i] = readReg(i);
    }
    return regs;
}
