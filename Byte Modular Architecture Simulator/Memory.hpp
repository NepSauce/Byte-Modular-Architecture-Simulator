#ifndef MEMORY_HPP
#define MEMORY_HPP

#include <cstdint>

static const uint32_t MEM_SIZE = 4096;

class Memory {
private:
    // Simulates 4 KBs of memory
    uint8_t memoryCell[MEM_SIZE];

public:
    /*
    * Sets all memoryGrid addresses to 0 
    */
    Memory();
    /*
    * Reads four Bytes of memory
    * Parameters: uint32_t addr (Read Address)
    * Return: uint32_t (Byte Group at Address addr)
    */
    uint32_t readMem32Bit(uint32_t addr) const;
    /*
    * Writes four Bytes to memory
    * Parameters: uint32_t addr (Read Address), uint32_t set (Set Value)
    */
    void writeMem32Bit(uint32_t addr, uint32_t set);
    /*
    * Reads one Byte of memory
    * Parameters: uint8_t addr (Read Address)
    * Return: uint8_t (Byte Group at Address addr)
    */
    uint8_t readMem8Bit(uint8_t addr) const;
    /*
    * Writes one Byte to memory
    * Parameters: uint8_t addr (Read Address), uint8_t set (Set Value)
    */
    void writeMem8Bit(uint8_t addr, uint8_t set);
};

#endif
