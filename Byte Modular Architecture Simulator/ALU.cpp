#include "ALU.hpp"

uint32_t ALU::execute(uint32_t a, uint32_t b, ALUOp op) {
    uint32_t result = 0;

    switch (op) {
        case ALUOp::ALU_OP_ADD:
            result = a + b;
            break;
        case ALUOp::ALU_OP_SUB:
            result = a - b;
            break;
        case ALUOp::ALU_OP_AND:
            result = a & b;
            break;
        case ALUOp::ALU_OP_OR:
            result = a | b;
            break;
        case ALUOp::ALU_OP_XOR:
            result = a ^ b;
            break;
        case ALUOp::ALU_OP_NOT:
            result = ~a;  
            break;
        case ALUOp::ALU_OP_SHL:
            result = a << (b & 0x1F);  
            break;
        case ALUOp::ALU_OP_SHR:
            result = a >> (b & 0x1F);  
            break;
        case ALUOp::ALU_OP_SRA:
            result = static_cast<int32_t>(a) >> (b & 0x1F);  
            break;
        case ALUOp::ALU_OP_SLT:
            result = (static_cast<int32_t>(a) < static_cast<int32_t>(b)) ? 1 : 0;
            break;
    }
    zero = (result == 0);

    return result;
}

bool ALU::zeroFlag() const {
    return zero;
}
