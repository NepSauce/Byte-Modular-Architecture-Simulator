#ifndef REGISTERFILE_HPP
#define REGISTERFILE_HPP

#include <cstdint>
#include <array>

class RegisterFile {
private:
    uint32_t registers[32];

public:
    RegisterFile();                          
    uint32_t readReg(uint8_t addr) const;      
    void writeReg(uint8_t addr, uint32_t set); 
    void resetAllReg();  

    std::array<uint32_t, 32> getAllRegisters() const;
};

#endif
