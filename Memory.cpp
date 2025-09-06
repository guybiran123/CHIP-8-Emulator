#include "Memory.h"

Memory::Memory(std::string fileName) {
	setFont();
	loadFileToMemory(fileName);
}

uint8_t Memory::readMemory(uint16_t address) const {
	if (address < 4096) {
		return memory[address];
	}
	return 0;
}

void Memory::writeMemory(uint16_t address, uint8_t value) {
	if (address < 4096) {
		memory[address] = value;
	}
}

uint16_t Memory::readOpcode(uint16_t& PC) const {
	uint8_t firstByte{ memory[PC++] };
	uint8_t secondByte{ memory[PC++] };
	uint16_t opcode{ firstByte };
	opcode <<= 8;
	opcode |= secondByte;

	return opcode;

}

void Memory::setFont() {
	const std::array<uint8_t, 80> strikes{
		0xF0, 0x90, 0x90, 0x90, 0xF0,  // 0
		0x20, 0x60, 0x20, 0x20, 0x70,  // 1
		0xF0, 0x10, 0xF0, 0x80, 0xF0,  // 2
		0xF0, 0x10, 0xF0, 0x10, 0xF0,  // 3
		0x90, 0x90, 0xF0, 0x10, 0x10,  // 4
		0xF0, 0x80, 0xF0, 0x10, 0xF0,  // 5
		0xF0, 0x80, 0xF0, 0x90, 0xF0,  // 6
		0xF0, 0x10, 0x20, 0x40, 0x40,  // 7
		0xF0, 0x90, 0xF0, 0x90, 0xF0,  // 8
		0xF0, 0x90, 0xF0, 0x10, 0xF0,  // 9
		0xF0, 0x90, 0xF0, 0x90, 0x90,  // A
		0xE0, 0x90, 0xE0, 0x90, 0xE0,  // B
		0xF0, 0x80, 0x80, 0x80, 0xF0,  // C
		0xE0, 0x90, 0x90, 0x90, 0xE0,  // D
		0xF0, 0x80, 0xF0, 0x80, 0xF0,  // E
		0xF0, 0x80, 0xF0, 0x80, 0x80 };// F
	for (int i{ 0 }; i < 80; ++i) {
		memory[0x50 + i] = strikes[i];
	}
}

void Memory::loadFileToMemory(std::string fileName) {
	std::ifstream File(fileName, std::ios::binary);
	if (!File.is_open()) {
		std::cerr << "Failed to open the file." << std::endl;
		return; 
	}
	uint8_t byte{};
	int address{ 512 };
	while (File.read(reinterpret_cast<char*>(&byte), sizeof(uint8_t))) {
		writeMemory(address++, byte);
	}

	File.close();

}