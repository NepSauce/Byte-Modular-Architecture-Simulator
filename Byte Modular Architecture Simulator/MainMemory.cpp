#include "MainMemory.hpp"

MainMemory::MainMemory() {
    for (int i = 0; i < 256; i++) {
        memoryCell[i] = 0;
    }
}

uint32_t MainMemory::readMem32Bit(uint32_t addr) const {
    return memoryCell[addr];
}

void MainMemory::writeMem32Bit(uint32_t addr, uint32_t set) {
    memoryCell[addr] = set;
}

uint8_t MainMemory::readMem8Bit(uint8_t addr) const {
    return memoryCell[addr];
}

void MainMemory::writeMem8Bit(uint8_t addr, uint8_t set) {
    memoryCell[addr] = set;
}
