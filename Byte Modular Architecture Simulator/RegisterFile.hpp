#ifndef REGISTERFILE_HPP
#define REGISTERFILE_HPP

#include <cstdint>

class RegisterFile {
private:
    uint32_t registers[32];

public:
    RegisterFile();                          
    uint32_t readReg(uint8_t addr) const;      
    void writeReg(uint8_t addr, uint32_t set); 
    void resetAllReg();                           
};

#endif
