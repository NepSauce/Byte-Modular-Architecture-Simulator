#include "ALU.hpp"

uint32_t ALU::execute(uint32_t inputA, uint32_t inputB, ALUOp op) {
	switch (op) {
		case ALUOp::ALU_OP_ADD:
			return inputA + inputB;
			break;
		case ALUOp::ALU_OP_SUB:
			return inputA - inputB;
			break;
		case ALUOp::ALU_OP_AND:
			return inputA & inputB;
			break;
		case ALUOp::ALU_OP_OR:
			return inputA | inputB;
			break;
		case ALUOp::ALU_OP_XOR:
			return inputA ^ inputB;
			break;
		case ALUOp::ALU_OP_NOT:
			return ~inputA;
			break;
		case ALUOp::ALU_OP_SHL:
			return inputA << (inputB & 0x1F);
			break;
		case ALUOp::ALU_OP_SHR:
			return inputA >> (inputB & 0x1F);
			break;
		case ALUOp::ALU_OP_SRA:
			return static_cast<int32_t>(inputA) >> (inputB & 0x1F);
			break;
		case ALUOp::ALU_OP_SLT:
			return (static_cast<int32_t>(inputA) < static_cast<int32_t>(inputB)) ? 1 : 0;
			break;
	}
}

