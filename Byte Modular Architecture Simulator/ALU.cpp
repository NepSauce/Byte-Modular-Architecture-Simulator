#include "ALU.hpp"

uint32_t ALU::execute(uint32_t a, uint32_t b, ALUOp op) {
    uint32_t result = 0;

    switch (op) {
        case ALUOp::ADD:
            result = a + b;
            break;
        case ALUOp::SUB:
            result = a - b;
            break;
        case ALUOp::AND:
            result = a & b;
            break;
        case ALUOp::OR:
            result = a | b;
            break;
        case ALUOp::XOR:
            result = a ^ b;
            break;
        case ALUOp::NOT:
            result = ~a;  
            break;
        case ALUOp::SHL:
            result = a << (b & 0x1F);  
            break;
        case ALUOp::SHR:
            result = a >> (b & 0x1F);  
            break;
        case ALUOp::SRA:
            result = static_cast<int32_t>(a) >> (b & 0x1F);  
            break;
        case ALUOp::SLT:
            result = (static_cast<int32_t>(a) < static_cast<int32_t>(b)) ? 1 : 0;
            break;
    }
    zero = (result == 0);

    return result;
}

bool ALU::zeroFlag() const {
    return zero;
}
