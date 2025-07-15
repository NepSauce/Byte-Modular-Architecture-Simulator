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
	}
}