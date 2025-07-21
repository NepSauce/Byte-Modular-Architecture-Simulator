#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

enum class ALUOp {
    ALU_OP_ADD = 0x00, // Addition
    ALU_OP_SUB = 0x01, // Subtraction
    ALU_OP_AND = 0x02, // Bitwise AND
    ALU_OP_OR = 0x03,  // Bitwise OR
    ALU_OP_XOR = 0x04, // Bitwise XOR
    ALU_OP_NOT = 0x05, // Bitwise NOT 
    ALU_OP_SHL = 0x06, // Shift Left Logical
    ALU_OP_SHR = 0x07, // Shift Right Logical
    ALU_OP_SRA = 0x08, // Shift Right Arithmetic
    ALU_OP_SLT = 0x09,  // Set on less than
    ALU_OP_SLL = 0x0A, // Shift Left Logical
    ALU_OP_SRL = 0x0B, // Shift Right Logical
    ALU_OP_NOR = 0x0C  // Bitwise NOR
};

class ALU {
public:
    uint32_t execute(uint32_t inputA, uint32_t inputB, ALUOp op);
    bool zeroFlag() const;

private:
    bool zero;
};

#endif 