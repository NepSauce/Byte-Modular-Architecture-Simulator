#ifndef CONTROL_UNIT_HPP
#define CONTROL_UNIT_HPP

#include <cstdint>

enum class ALUControl {
	ADD,
	SUB,
	AND,
	OR,
	SLT,
	NOP
};

struct ControlSignals {
    bool regDst;       // 1 = use rd, 0 = use rt (dest register)
    bool aluSrc;       // 1 = use immediate, 0 = use register
    bool memToReg;     // 1 = write data from memory, 0 = from ALU
    bool regWrite;     // Enable register write
    bool memRead;      // Enable memory read
    bool memWrite;     // Enable memory write
    bool branch;       // Branch instruction (beq)
    bool jump;         // Jump instruction (j)
    ALUControl ALUOp;  // ALU operation selector
};

class ControlUnit {
public:
    ControlSignals decode(uint8_t opcode);
};
#endif 
