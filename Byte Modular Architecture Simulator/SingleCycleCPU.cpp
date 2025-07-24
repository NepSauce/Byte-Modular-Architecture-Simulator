#include "SingleCycleCPU.hpp"

SingleCycleCPU::SingleCycleCPU(MainMemory& mem, RegisterFile& reg)
    : memory(mem), regFile(reg), pc(0) { }

void SingleCycleCPU::reset() {
    pc = 0;
    regFile.resetAllReg();
}

void SingleCycleCPU::step() {

}