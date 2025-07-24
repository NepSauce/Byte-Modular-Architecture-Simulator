#ifndef ALU_HPP
#define ALU_HPP

#include <cstdint>

enum class ALUOp {
    ADD,
    SUB,
    AND,
    OR,
    XOR,
    NOT,
    SHL,
    SHR,
    SRA,
    SLT,
    NOR,
    SLL,
    SRL,
    NOP
};

class ALU {
public:
    uint32_t execute(uint32_t inputA, uint32_t inputB, ALUOp op);
    bool zeroFlag() const;

private:
    bool zero;
};

#endif 