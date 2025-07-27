// CPU.cpp
#include "CPU.hpp"
#include <iostream>
#include <iomanip>

// Constructor initializes PC to zero
CPU::CPU() : PC(0) {}

// Set PC externally
void CPU::setPC(uint32_t addr) {
    PC = addr;
}

uint32_t CPU::getPC() const {
    return PC;
}

uint32_t CPU::readRegister(uint8_t regNum) const {
    return registers.readReg(regNum);
}

uint32_t CPU::readMemory(uint32_t addr) const {
    return memory.readMem32Bit(addr);
}

void CPU::step() {
    // 1. FETCH instruction (32-bit) from memory at PC
    uint32_t instruction = memory.readMem32Bit(PC);

    // Print PC and raw instruction
    std::cout << "PC = 0x" << std::hex << PC
        << " | Instruction = 0x" << std::setw(8) << std::setfill('0') << instruction << std::dec << "\n";

    // Extract fields from instruction
    uint8_t opcode = (instruction >> 26) & 0x3F;  // bits 31-26
    uint8_t rs = (instruction >> 21) & 0x1F;     // bits 25-21
    uint8_t rt = (instruction >> 16) & 0x1F;     // bits 20-16
    uint8_t rd = (instruction >> 11) & 0x1F;     // bits 15-11
    uint8_t shamt = (instruction >> 6) & 0x1F;   // bits 10-6
    uint8_t funct = instruction & 0x3F;          // bits 5-0
    int16_t imm = instruction & 0xFFFF;          // bits 15-0 immediate
    uint32_t addr = instruction & 0x3FFFFFF;     // bits 25-0 (jump address)

    // Print decoded fields
    std::cout << "opcode=" << (int)opcode << " rs=$" << (int)rs << " rt=$" << (int)rt
        << " rd=$" << (int)rd << " shamt=" << (int)shamt << " funct=0x" << std::hex << (int)funct << std::dec << "\n";
    std::cout << "imm=" << imm << " addr=0x" << std::hex << addr << std::dec << "\n";

    // 2. Generate control signals
    ControlSignals ctrl = controlUnit.generateControl(opcode, funct);

    // 3. Read registers
    uint32_t regRsVal = registers.readReg(rs);
    uint32_t regRtVal = registers.readReg(rt);
    std::cout << "Read Registers: $" << (int)rs << "=" << regRsVal << ", $" << (int)rt << "=" << regRtVal << "\n";

    // 4. Determine ALU input B
    uint32_t aluInputB = ctrl.aluSrc ? static_cast<int32_t>(imm) : regRtVal;
    std::cout << "ALU Inputs: A=" << regRsVal << ", B=" << aluInputB << "\n";

    // 5. Select destination register
    uint8_t writeReg = ctrl.regDst ? rd : rt;

    // 6. ALU operation
    uint32_t aluResult = alu.execute(regRsVal, aluInputB, ctrl.ALUOp);
    std::cout << "ALU Result = " << aluResult << " | Zero flag = " << alu.zeroFlag() << "\n";

    // 7. Branch decision
    bool takeBranch = ctrl.branch && alu.zeroFlag();
    std::cout << "Branch: " << (takeBranch ? "TAKEN" : "NOT taken") << "\n";

    // 8. Memory operations
    uint32_t memData = 0;
    if (ctrl.memRead) {
        memData = memory.readMem32Bit(aluResult);
        std::cout << "Memory Read: Address=0x" << std::hex << aluResult << std::dec << " Data=" << memData << "\n";
    }
    if (ctrl.memWrite) {
        memory.writeMem32Bit(aluResult, regRtVal);
        std::cout << "Memory Write: Address=0x" << std::hex << aluResult << std::dec << " Data=" << regRtVal << "\n";
    }

    // 9. Write back to register if enabled
    if (ctrl.regWrite) {
        uint32_t writeData = ctrl.memToReg ? memData : aluResult;
        if (writeReg != 0) {  // Register 0 is always zero in MIPS
            registers.writeReg(writeReg, writeData);
            std::cout << "Write Register: $" << (int)writeReg << " = " << writeData << "\n";
        }
    }

    // 10. Update PC
    uint32_t oldPC = PC;
    PC += 4;  // Default next instruction

    if (takeBranch) {
        int32_t branchOffset = static_cast<int32_t>(imm) << 2;
        PC += branchOffset;
        std::cout << "Branch taken. PC updated by offset: " << branchOffset << "\n";
    }

    if (ctrl.jump) {
        PC = (oldPC & 0xF0000000) | (addr << 2);
        std::cout << "Jump taken. PC set to: 0x" << std::hex << PC << std::dec << "\n";
    }

    std::cout << "Next PC = 0x" << std::hex << PC << std::dec << "\n";
    std::cout << "----------------------------------------\n";
}

void CPU::loadProgram(const std::vector<uint32_t>& program) {
    // Load each 32-bit instruction as 4 bytes into memory starting at address 0
    uint32_t addr = 0;
    for (uint32_t instr : program) {
        memory.writeMem8Bit(addr, (instr >> 24) & 0xFF);
        memory.writeMem8Bit(addr + 1, (instr >> 16) & 0xFF);
        memory.writeMem8Bit(addr + 2, (instr >> 8) & 0xFF);
        memory.writeMem8Bit(addr + 3, instr & 0xFF);
        addr += 4;
    }
    PC = 0;  // Reset PC to start of program
}
