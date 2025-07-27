#ifndef CPU_HPP  
#define CPU_HPP  

#include "RegisterFile.hpp"  
#include "MainMemory.hpp"  
#include "ControlUnit.hpp"  
#include "ALU.hpp"  
#include <cstdint>  
#include <vector>  

class CPU {  
private:  
    RegisterFile registers;  
    MainMemory memory;  
    ControlUnit controlUnit;  
    ALU alu;  

    uint32_t PC;  // Program Counter  

public:  
    CPU();  

    // Run one instruction cycle: fetch, decode, execute, memory, writeback  
    void step();  

    // For testing/debugging: set PC  
    void setPC(uint32_t addr);  

    // For testing/debugging: get PC  
    uint32_t getPC() const;  

    // For testing/debugging: access registers  
    uint32_t readRegister(uint8_t regNum) const;  

    // For testing/debugging: access memory  
    uint32_t readMemory(uint32_t addr) const;  

    // Load a program into memory  
    void loadProgram(const std::vector<uint32_t>& program);  
};  

#endif
