#include "ControlUnit.hpp"

ControlSignals ControlUnit::generateControl(uint8_t opcode, uint8_t funct) {
	ControlSignals signals = {};

	switch (opcode) {
		case 0x00: // R-type instructions
			signals.regDst = true;
			signals.aluSrc = false;
			signals.memToReg = false;
			signals.regWrite = true;
			signals.memRead = false;
			signals.memWrite = false;
			signals.branch = false;
			signals.jump = false;

            switch (funct) {
                case 0x20: signals.ALUOp = ALUOp::ADD; break;  // add
                case 0x22: signals.ALUOp = ALUOp::SUB; break;  // sub
                case 0x24: signals.ALUOp = ALUOp::AND; break;  // and
                case 0x25: signals.ALUOp = ALUOp::OR;  break;  // or
                case 0x2A: signals.ALUOp = ALUOp::SLT; break;  // slt
                case 0x27: signals.ALUOp = ALUOp::NOR; break;  // nor
                case 0x00: signals.ALUOp = ALUOp::SLL; break;  // sll
                case 0x02: signals.ALUOp = ALUOp::SRL; break;  // srl
                default:   signals.ALUOp = ALUOp::ADD; break;  // fallback
            }
            break;

		case 0x23: // lw instruction
			signals.regDst = false;
			signals.aluSrc = true;
			signals.memToReg = true;
			signals.regWrite = true;
			signals.memRead = true;
			signals.memWrite = false;
			signals.branch = false;
			signals.jump = false;
			signals.ALUOp = ALUOp::ADD;
			break;

        case 0x2B: // sw
            signals.regDst = false;
            signals.aluSrc = true;
            signals.memToReg = false;
            signals.regWrite = false;
            signals.memRead = false;
            signals.memWrite = true;
            signals.branch = false;
            signals.jump = false;
            signals.ALUOp = ALUOp::ADD;
            break;

        case 0x04: // beq
            signals.regDst = false;
            signals.aluSrc = false;
            signals.memToReg = false;
            signals.regWrite = false;
            signals.memRead = false;
            signals.memWrite = false;
            signals.branch = true;
            signals.jump = false;
            signals.ALUOp = ALUOp::SUB;
            break;

        case 0x02: // j
            signals.regDst = false;
            signals.aluSrc = false;
            signals.memToReg = false;
            signals.regWrite = false;
            signals.memRead = false;
            signals.memWrite = false;
            signals.branch = false;
            signals.jump = true;
            signals.ALUOp = ALUOp::NOP;
            break;

        case 0x08: // addi
            signals.regDst = false;       
            signals.aluSrc = true;        
            signals.memToReg = false;     
            signals.regWrite = true;
            signals.memRead = false;
            signals.memWrite = false;
            signals.branch = false;
            signals.jump = false;
            signals.ALUOp = ALUOp::ADD;
            break;

        default:
            signals = {};
            signals.ALUOp = ALUOp::NOP;
            break;
    }

    return signals;
}

