#include "Stack.h"

void Stack::push(uint16_t value) {
	stack.push_back(value);
}

uint16_t Stack::pop() {
	uint16_t topElement{ stack.back() };
	stack.pop_back();
	return topElement;
}