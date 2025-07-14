#include <iostream>
#include <iomanip>

#include "MainMemory.hpp"
#include "RegisterFile.hpp"

int main() {
    MainMemory mem;
    RegisterFile regs;

    uint32_t testAddr = 0x10;
    uint32_t testVal = 0x12345678;

    mem.writeMem32Bit(testAddr, testVal);
    uint32_t result = mem.readMem32Bit(testAddr);

    std::cout << "Wrote 0x" << std::hex << testVal
        << " to address 0x" << testAddr << "\n";
    std::cout << "Read back: 0x" << std::hex << result << "\n";

    std::cout << "Byte at 0x10: 0x" << std::hex << static_cast<int>(mem.readMem8Bit(0x10)) << "\n";

    std::cout << "\n===== REGISTER TESTS =====\n";

    regs.writeReg(5, 0xCAFEBABE);
    std::cout << "$5 = 0x" << std::hex << regs.readReg(5) << "\n";

    regs.writeReg(0, 0xFFFFFFFF);
    std::cout << "$0 (zero) = 0x" << std::hex << regs.readReg(0) << " (should be 0)\n";

    return 0;
}
