#pragma once
#include <cstdint>
#include "RegisterFile.hpp"
#include "MainMemory.hpp"
#include "ControlUnit.hpp"

class CPU {
public:
    CPU(MainMemory& mem, RegisterFile& rf);

    void reset();
    void loadInstruction(uint32_t addr, uint32_t instruction); 
    void runNextInstruction(); 
    uint32_t getPC() const;
    std::array<uint32_t, 32> getRegisters() const;

private:
    uint32_t pc;
    MainMemory& memory;
    RegisterFile& regFile;
    ControlUnit controlUnit;

    uint32_t signExtend16(uint16_t val);
    void executeRType(uint32_t instruction, const ControlSignals& ctrl);
    void executeIType(uint32_t instruction, const ControlSignals& ctrl);
    void executeJType(uint32_t instruction, const ControlSignals& ctrl);
};