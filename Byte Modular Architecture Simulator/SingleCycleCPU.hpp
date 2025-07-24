#ifndef SINGLECYCLECPU_CPP
#define SINGLECYCLECPU_CPP

#include "MainMemory.hpp"
#include "RegisterFile.hpp"
#include "ALU.hpp"
#include "ControlUnit.hpp"

#include <vector>
#include <cstdint>

class SingleCycleCPU {
private:
	uint32_t pc;

	MainMemory& memory;
	RegisterFile& regFile;
	ALU alu;
	ControlUnit controlUnit;
public:
	SingleCycleCPU(MainMemory& mem, RegisterFile& reg);

	void reset();
	void step();
};



#endif