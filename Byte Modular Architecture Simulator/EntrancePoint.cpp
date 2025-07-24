#include <iostream>
#include <cassert>

#include "RegisterFile.hpp"
#include "MainMemory.hpp"
#include "ControlUnit.hpp"
#include "ALU.hpp"

// --- Register File Test ---
void testRegisterFile() {
    RegisterFile rf;

    rf.writeReg(1, 123);
    rf.writeReg(2, 456);

    assert(rf.readReg(1) == 123);
    assert(rf.readReg(2) == 456);

    // Register 0 should always be 0
    rf.writeReg(0, 999);
    assert(rf.readReg(0) == 0);

    rf.resetAllReg();
    assert(rf.readReg(1) == 0);
    assert(rf.readReg(2) == 0);

    std::cout << "RegisterFile passed.\n";
}

// --- Main Memory Test ---
void testMainMemory() {
    MainMemory mem;

    mem.writeMem32Bit(0, 0x12345678);
    assert(mem.readMem32Bit(0) == 0x12345678);

    mem.writeMem8Bit(4, 0xAB);
    assert(mem.readMem8Bit(4) == 0xAB);

    mem.writeMem32Bit(100, 0xCAFEBABE);
    assert(mem.readMem32Bit(100) == 0xCAFEBABE);

    std::cout << "MainMemory passed.\n";
}

// --- ALU Test ---
void testALU() {
    ALU alu;

    assert(alu.execute(10, 5, ALUOp::ALU_OP_ADD) == 15);
    assert(alu.execute(10, 5, ALUOp::ALU_OP_SUB) == 5);
    assert(alu.execute(10, 5, ALUOp::ALU_OP_AND) == (10 & 5));
    assert(alu.execute(10, 5, ALUOp::ALU_OP_OR) == (10 | 5));
    assert(alu.execute(10, 5, ALUOp::ALU_OP_XOR) == (10 ^ 5));
    assert(alu.execute(10, 0, ALUOp::ALU_OP_NOT) == ~10);
    assert(alu.execute(2, 2, ALUOp::ALU_OP_SHL) == (2 << 2));
    assert(alu.execute(8, 2, ALUOp::ALU_OP_SHR) == (8 >> 2));
    assert(alu.execute(0xFFFFFFF0, 2, ALUOp::ALU_OP_SRA) == int32_t(0xFFFFFFF0) >> 2);
    assert(alu.execute(3, 5, ALUOp::ALU_OP_SLT) == 1);
    assert(alu.execute(5, 3, ALUOp::ALU_OP_SLT) == 0);
    assert(alu.execute(0xF0F0F0F0, 0x0F0F0F0F, ALUOp::ALU_OP_NOR) == ~(0xF0F0F0F0 | 0x0F0F0F0F));

    std::cout << "ALU passed.\n";
}

// --- Control Unit Test ---
void testControlUnit() {
    ControlUnit cu;

    ControlSignals rtype = cu.generateControl(0x00, 0x20); // add
    assert(rtype.regDst == true);
    assert(rtype.aluSrc == false);
    assert(rtype.regWrite == true);
    assert(rtype.ALUOp == ALUControl::ADD);

    ControlSignals lw = cu.generateControl(0x23); // lw
    assert(lw.memRead == true);
    assert(lw.memToReg == true);
    assert(lw.aluSrc == true);

    ControlSignals sw = cu.generateControl(0x2B); // sw
    assert(sw.memWrite == true);
    assert(sw.regWrite == false);

    ControlSignals beq = cu.generateControl(0x04); // beq
    assert(beq.branch == true);
    assert(beq.ALUOp == ALUControl::SUB);

    ControlSignals jump = cu.generateControl(0x02); // j
    assert(jump.jump == true);

    std::cout << "ControlUnit passed.\n";
}

int main() {
    testRegisterFile();
    testMainMemory();
    testALU();
    testControlUnit();

    std::cout << "\nAll component tests passed successfully.\n";
    return 0;
}
