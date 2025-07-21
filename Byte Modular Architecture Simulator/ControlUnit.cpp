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
				
			}
			break;
	};
}