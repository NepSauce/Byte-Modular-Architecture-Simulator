#include "CPU.hpp"
#include <iostream>

CPU::CPU(MainMemory& mem, RegisterFile& rf)
    : pc(0), memory(mem), regFile(rf) {
}

void CPU::reset() {
    pc = 0;
    regFile.resetAllReg();
}

void CPU::loadInstruction(uint32_t addr, uint32_t instruction) {
    memory.writeMem32Bit(addr, instruction);
}

uint32_t CPU::getPC() const {
    return pc;
}

uint32_t CPU::signExtend16(uint16_t val) {
    // Sign-extend 16-bit immediate to 32-bit
    if (val & 0x8000) {
        return 0xFFFF0000 | val;
    }
    return val;
}

void CPU::runNextInstruction() {
    uint32_t instr = memory.readMem32Bit(pc);

    uint8_t opcode = (instr >> 26) & 0x3F;
    uint8_t rs = (instr >> 21) & 0x1F;
    uint8_t rt = (instr >> 16) & 0x1F;
    uint8_t rd = (instr >> 11) & 0x1F;
    uint8_t shamt = (instr >> 6) & 0x1F;
    uint8_t funct = instr & 0x3F;
    uint16_t immediate = instr & 0xFFFF;
    uint32_t address = instr & 0x03FFFFFF;

    ControlSignals ctrl = controlUnit.generateControl(opcode, funct);

    if (opcode == 0x00) {
        // R-Type
        executeRType(instr, ctrl);
        pc += 4;
    }
    else if (opcode == 0x02) {
        // Jump
        executeJType(instr, ctrl);
    }
    else {
        // I-Type (lw, sw, beq)
        executeIType(instr, ctrl);
    }
}

void CPU::executeRType(uint32_t instr, const ControlSignals& ctrl) {
    uint8_t rs = (instr >> 21) & 0x1F;
    uint8_t rt = (instr >> 16) & 0x1F;
    uint8_t rd = (instr >> 11) & 0x1F;
    uint8_t shamt = (instr >> 6) & 0x1F;
    uint8_t funct = instr & 0x3F;

    uint32_t valRs = regFile.readReg(rs);
    uint32_t valRt = regFile.readReg(rt);
    uint32_t aluResult = 0;

    switch (ctrl.ALUOp) {
        case ALUOp::ADD:
            aluResult = valRs + valRt;
            break;
        case ALUOp::SUB:
            aluResult = valRs - valRt;
            break;
        case ALUOp::AND:
            aluResult = valRs & valRt;
            break;
        case ALUOp::OR:
            aluResult = valRs | valRt;
            break;
        case ALUOp::SLT:
            aluResult = (int32_t(valRs) < int32_t(valRt)) ? 1 : 0;
            break;
        case ALUOp::NOR:
            aluResult = ~(valRs | valRt);
            break;
        case ALUOp::SLL:
            aluResult = valRt << shamt;
            break;
        case ALUOp::SRL:
            aluResult = valRt >> shamt;
            break;
        default:
            aluResult = 0;
    }

    if (ctrl.regWrite) {
        regFile.writeReg(rd, aluResult);
    }
}

void CPU::executeIType(uint32_t instr, const ControlSignals& ctrl) {
    uint8_t rs = (instr >> 21) & 0x1F;
    uint8_t rt = (instr >> 16) & 0x1F;
    uint16_t imm = instr & 0xFFFF;
    uint32_t signExtImm = signExtend16(imm);

    uint32_t valRs = regFile.readReg(rs);

    uint32_t aluInput2 = ctrl.aluSrc ? signExtImm : regFile.readReg(rt);

    uint32_t aluResult = 0;
    switch (ctrl.ALUOp) {
    case ALUOp::ADD:
        aluResult = valRs + aluInput2;
        break;
    case ALUOp::SUB:
        aluResult = valRs - aluInput2;
        break;
    default:
        aluResult = 0;
        break;
    }

    if (ctrl.memRead) {
        uint32_t memData = memory.readMem32Bit(aluResult);
        if (ctrl.regWrite) {
            regFile.writeReg(rt, memData);
        }
    }
    else if (ctrl.memWrite) {
        memory.writeMem32Bit(aluResult, regFile.readReg(rt));
    }
    else if (ctrl.branch) {
        // BEQ: if rs == rt then branch
        if (valRs == regFile.readReg(rt)) {
            pc += 4 + (signExtImm << 2);
            return;
        }
    }
    else if (ctrl.regWrite) {
        regFile.writeReg(rt, aluResult);
    }

    pc += 4;
}

void CPU::executeJType(uint32_t instr, const ControlSignals& ctrl) {
    // Jump address is upper 4 bits of PC+4 concatenated with 26-bit address << 2
    uint32_t address = instr & 0x03FFFFFF;
    uint32_t target = (pc & 0xF0000000) | (address << 2);
    pc = target;
}

std::array<uint32_t, 32> CPU::getRegisters() const {
    return regFile.getAllRegisters();
}