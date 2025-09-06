#pragma once
#include <cstdint>
#include <array>
#include <string>
#include <sstream>
#include <cctype>
#include <fstream>
#include <iostream>


class Memory {
private:
	std::array<uint8_t, 4096> memory{};

public:
	Memory(std::string fileName);

	uint8_t readMemory(uint16_t address) const;

	void writeMemory(uint16_t address, uint8_t value);

	uint16_t readOpcode(uint16_t& PC) const;

	void setFont();

	void loadFileToMemory(std::string fileName);
};