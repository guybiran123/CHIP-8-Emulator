#pragma once
#include <cstdint>
#include <vector>

class Stack {
private:
	std::vector<uint16_t> stack{};

public:
	Stack() = default;

	void push(uint16_t value);

	uint16_t pop();
};