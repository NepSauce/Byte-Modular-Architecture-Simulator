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
				case 0x20: signals.ALUOp = ALUControl::ADD; break; // add
				case 0x22: signals.ALUOp = ALUControl::SUB; break; // sub
				case 0x24: signals.ALUOp = ALUControl::AND; break; // and
				case 0x25: signals.ALUOp = ALUControl::OR;  break; // or
				case 0x2A: signals.ALUOp = ALUControl::SLT; break; // slt
				case 0x27: signals.ALUOp = ALUControl::NOR; break; // nor
				case 0x00: signals.ALUOp = ALUControl::SLL; break; // sll
				case 0x02: signals.ALUOp = ALUControl::SRL; break; // srl
				default:   signals.ALUOp = ALUControl::ADD; break; // fallback
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
			signals.ALUOp = ALUControl::ADD; 
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
            signals.ALUOp = ALUControl::ADD;
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
            signals.ALUOp = ALUControl::SUB;
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
            signals.ALUOp = ALUControl::NOP;
            break;

        default:
            signals = {};
            signals.ALUOp = ALUControl::NOP;
            break;
    }

    return signals;
}

