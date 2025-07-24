#ifndef CONTROL_UNIT_HPP
#define CONTROL_UNIT_HPP

#include "ALU.hpp"

#include <cstdint>


struct ControlSignals {
    bool regDst;       // 1 = use rd, 0 = use rt (dest register)
    bool aluSrc;       // 1 = use immediate, 0 = use register
    bool memToReg;     // 1 = write data from memory, 0 = from ALU
    bool regWrite;     // Enable register write
    bool memRead;      // Enable memory read
    bool memWrite;     // Enable memory write
    bool branch;       // Branch instruction (beq)
    bool jump;         // Jump instruction (j)
    ALUOp ALUOp;       // ALU operation selector
};

class ControlUnit {
public:
    ControlSignals generateControl(uint8_t opcode, uint8_t funct = 0);
};
#endif 
