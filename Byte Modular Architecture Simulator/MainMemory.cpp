#include "MainMemory.hpp"

MainMemory::MainMemory() {
    for (int i = 0; i < 256; i++) {
        memoryCell[i] = 0;
    }
}

uint32_t MainMemory::readMem32Bit(uint32_t addr) const {
    return (memoryCell[addr + 0] << 24) |
        (memoryCell[addr + 1] << 16) |
        (memoryCell[addr + 2] << 8) |
        (memoryCell[addr + 3]);
}

void MainMemory::writeMem32Bit(uint32_t addr, uint32_t set) {
    memoryCell[addr + 0] = (set >> 24) & 0xFF;  
    memoryCell[addr + 1] = (set >> 16) & 0xFF;
    memoryCell[addr + 2] = (set >> 8) & 0xFF;
    memoryCell[addr + 3] = set & 0xFF;         
}

uint8_t MainMemory::readMem8Bit(uint8_t addr) const {
    return memoryCell[addr];
}

void MainMemory::writeMem8Bit(uint8_t addr, uint8_t set) {
    memoryCell[addr] = set;
}