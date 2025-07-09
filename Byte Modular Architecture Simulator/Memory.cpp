#include "Memory.hpp"

Memory::Memory() {
    for (int i = 0; i < 256; i++) {
        memoryCell[i] = 0;
    }
}

uint32_t Memory::readMem32Bit(uint32_t addr) const {
    return memoryCell[addr];
}

void Memory::writeMem32Bit(uint32_t addr, uint32_t set) {
    memoryCell[addr] = set;
}

uint8_t Memory::readMem8Bit(uint8_t addr) const {
    return memoryCell[addr];
}

void Memory::writeMem8Bit(uint8_t addr, uint8_t set) {
    memoryCell[addr] = set;
}
