#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include <sstream>
#include <iomanip>
#include <cstdint>
#include "CPU.hpp"

std::string trim(const std::string& s) {
    size_t start = s.find_first_not_of(" \t");
    if (start == std::string::npos) return "";
    size_t end = s.find_last_not_of(" \t");
    return s.substr(start, end - start + 1);
}

int regNum(const std::string& r) {
    if (r == "$zero") return 0;
    if (r == "$t0") return 8;
    if (r == "$t1") return 9;
    if (r == "$t2") return 10;
    if (r == "$t3") return 11;
    if (r == "$t4") return 12;
    if (r == "$t5") return 13;
    if (r == "$t6") return 14;
    if (r == "$t7") return 15;
    return 0; // default zero for simplicity
}

int16_t parseImm(const std::string& imm) {
    return static_cast<int16_t>(std::stoi(imm));
}

std::vector<std::string> split(const std::string& line) {
    std::vector<std::string> tokens;
    std::string token;
    for (char c : line) {
        if (c == ' ' || c == ',') {
            if (!token.empty()) {
                tokens.push_back(token);
                token.clear();
            }
        }
        else token.push_back(c);
    }
    if (!token.empty()) tokens.push_back(token);
    return tokens;
}

int main() {
    std::unordered_map<std::string, int> labels;
    std::vector<std::string> lines;
    std::vector<uint32_t> machineCode;

    int lineNum = 0;
    while (true) {
        std::string input;
        std::getline(std::cin, input);
        input = trim(input);
        if (input == "END" || input.empty()) break;

        size_t colon = input.find(':');
        if (colon != std::string::npos) {
            std::string label = trim(input.substr(0, colon));
            labels[label] = lineNum;
            input = trim(input.substr(colon + 1));
            if (input.empty()) continue;
        }
        lines.push_back(input);
        lineNum++;
    }

    for (int i = 0; i < (int)lines.size(); i++) {
        auto tokens = split(lines[i]);
        std::string instr = tokens[0];
        uint32_t code = 0;

        if (instr == "add" || instr == "sub") {
            int rd = regNum(tokens[1]);
            int rs = regNum(tokens[2]);
            int rt = regNum(tokens[3]);
            uint8_t funct = (instr == "add") ? 0x20 : 0x22;
            code = (0 << 26) | (rs << 21) | (rt << 16) | (rd << 11) | (0 << 6) | funct;
        }
        else if (instr == "lw" || instr == "sw") {
            int rt = regNum(tokens[1]);
            std::string offsetBase = tokens[2];
            size_t openPar = offsetBase.find('(');
            size_t closePar = offsetBase.find(')');
            int16_t offset = parseImm(offsetBase.substr(0, openPar));
            int rs = regNum(offsetBase.substr(openPar + 1, closePar - openPar - 1));
            uint8_t opcode = (instr == "lw") ? 0x23 : 0x2B;
            code = (opcode << 26) | (rs << 21) | (rt << 16) | (static_cast<uint16_t>(offset));
        }
        else if (instr == "beq") {
            int rs = regNum(tokens[1]);
            int rt = regNum(tokens[2]);
            std::string label = tokens[3];
            int16_t offset = labels[label] - (i + 1);
            code = (0x04 << 26) | (rs << 21) | (rt << 16) | (static_cast<uint16_t>(offset));
        }
        else if (instr == "j") {
            std::string label = tokens[1];
            uint32_t target = labels[label];
            code = (0x02 << 26) | (target & 0x03FFFFFF);
        }

        machineCode.push_back(code);

        CPU cpu;

        cpu.loadProgram(machineCode);

        while (cpu.getPC() < machineCode.size() * 4) {
            cpu.step();
        }
    }

    for (auto c : machineCode) {
        std::cout << std::hex << std::setw(8) << std::setfill('0') << c << "\n";
    }

    return 0;
}
