#include "OpcodesFunctions.h"

void op00E0_clear(Display& display) {
	display.clear();
	display.updateScreen();
}

void op00EE_return(Stack& stack, uint16_t& PC) {
	PC = stack.pop();
}

void op1NNN_jump(uint16_t NNN, uint16_t& PC) {
	PC = NNN;
}

void op2NNN_call(uint16_t NNN, Stack& stack, uint16_t& PC) {
	stack.push(PC);
	PC = NNN;
}

void op3XNN_skip(uint8_t VX, uint8_t NN, uint16_t& PC){
	if (VX == NN) {
		PC += 2;
	}
}

void op4XNN_skip(uint8_t VX, uint8_t NN, uint16_t& PC){
	if (VX != NN) {
		PC += 2;
	}
}

void op5XY0_skip(uint8_t VX, uint8_t VY, uint16_t& PC){
	if (VX == VY) {
		PC += 2;
	}
}

void op6XNN_set(uint8_t& VX, uint8_t NN) {
	VX = NN;
}

void op7XNN_add(uint8_t& VX, uint8_t NN) {
	VX += NN;
}

void op8XY0_set(uint8_t& VX, uint8_t VY){
	VX = VY;
}

void op8XY1_OR(uint8_t& VX, uint8_t VY){
	VX |= VY;
}

void op8XY2_AND(uint8_t& VX, uint8_t VY){
	VX &= VY;
}

void op8XY3_XOR(uint8_t& VX, uint8_t VY){
	VX ^= VY;
}

void op8XY4_add(uint8_t& VX, uint8_t VY, uint8_t& VF){
	if (VX + VY > 255) {
		VF = 1;
	}
	else {
		VF = 0;
	}
	VX += VY;
}

void op8XY5_subtract(uint8_t& VX, uint8_t VY, uint8_t& VF){
	if (VX > VY) {
		VF = 1;
	}
	else {
		VF = 0;
	}
	VX -= VY;
}

void op8XY6_shift(uint8_t& VX, uint8_t VY, uint8_t& VF){
	VX = VY;
	VF = VX & 0x0001;
	VX >>= 1;
}

void op8XY7_subtract(uint8_t& VX, uint8_t VY, uint8_t& VF){
	if (VY > VX) {
		VF = 1;
	}
	else {
		VF = 0;
	}
	VX = VY - VX;
}

void op8XYE_shift(uint8_t& VX, uint8_t VY, uint8_t& VF){
	VX = VY;
	VF = VX & 0x8000;
	VX <<= 1;
}

void op9XY0_skip(uint8_t VX, uint8_t VY, uint16_t& PC){
	if (VX != VY) {
		PC += 2;
	}
}

void opANNN_setI(uint16_t& I, uint16_t NNN) {
	I = NNN;
}

void opBXNN_jumpWithOffset(uint8_t VX, uint16_t XNN, uint16_t& PC) {
	PC = XNN + VX;
}

void opCXNN_random(uint8_t& VX, uint8_t NN) {
	uint8_t rand{ static_cast<uint8_t>(Random::get(0, 255)) };
	VX = rand & NN;
}

void opDXYN_display(Display& display, Memory& memory, uint8_t VX, uint8_t VY, uint8_t N, uint16_t I, uint8_t& VF) {
	int Xcoor{ };
	int Ycoor{ VY % 32 };
	VF = 0;
	uint8_t spriteRow{ };
	for (int i{ 0 }; i < N; ++i) {
		Xcoor = VX % 64;
		spriteRow = memory.readMemory(I + i);
		for (int j{ 7 }; j >= 0; --j) {
			if (Xcoor >= 64) {
				break;
			}
			bool spriteBit{ static_cast<bool>(spriteRow & (1 << j)) };
			if (spriteBit && display.isBitOn(Xcoor, Ycoor)) {
				display.turnOffBit(Xcoor, Ycoor);
				VF = 1;
			}
			else if (spriteBit && !display.isBitOn(Xcoor, Ycoor)) {
				display.turnOnBit(Xcoor, Ycoor);
			}
			++Xcoor;
		}
		++Ycoor;
		if (Ycoor >= 32) {
			break;
		}
	}
	display.updateScreen();
}

void opEX9E_skipIfKey(uint8_t VX, uint16_t& PC) {
	if (sf::Keyboard::isKeyPressed(KEYS[VX & 0x00FF])) {
		PC += 2;
	}
}

void opEXA1_skipIfKey(uint8_t VX, uint16_t& PC) {
	if (!sf::Keyboard::isKeyPressed(KEYS[VX & 0x00FF])) {
		PC += 2;
	}
}

void opFX07_timer(uint8_t& VX, uint8_t delayTimer, std::mutex& mtx) {
	mtx.lock();
	VX = delayTimer;
	mtx.unlock();
}

void opFX15_timer(uint8_t VX, uint8_t& delayTimer, std::mutex& mtx) {
	mtx.lock();
	delayTimer = VX;
	mtx.unlock();
}

void opFX18_timer(uint8_t VX, uint8_t& soundTimer, std::mutex& mtx) {
	mtx.lock();
	soundTimer = VX;
	mtx.unlock();
}

void opFX1E_addToIndex(uint8_t VX, uint16_t& I, uint8_t& VF) {
	if (VX + I >= 0x1000) {
		VF = 1;
	}
	I += VX;
}

void opFX29_font(uint8_t VX, uint16_t& I) {
	uint8_t ch{ static_cast<uint8_t>(VX & 0x00FF) };
	I = 80 + ch * 5;
}

void opFX33_decConversion(Memory& memory, uint8_t VX, uint16_t I) {
	memory.writeMemory(I, VX / 100);
	memory.writeMemory(I + 1, VX / 10 % 10);
	memory.writeMemory(I + 2, VX % 10);
}

void opFX55_storeMemory(Memory& memory, const std::array<uint8_t, 16>& V, uint8_t X, uint16_t I) {
	for (int i{ 0 }; i <= X; ++i) {
		memory.writeMemory(I + i, V[i]);
	}
}

void opFX65_loadMemory(const Memory& memory, std::array<uint8_t, 16>& V, uint8_t X, uint16_t I) {
	for (int i{ 0 }; i <= X; ++i) {
		V[i] = memory.readMemory(I + i);
	}
}

void opFX0A_getKey(Display& display, uint8_t& VX) {
	while (true) {
		sf::Event event;
		while (display.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				display.window.close();
			}
			else if (event.type == sf::Event::KeyPressed) {
				sf::Keyboard::Key keyPressed = event.key.code;
				for (int i{ 0 }; i < KEYS.size(); ++i) {
					if (KEYS[i] == keyPressed) {
						VX = i;
						return;
					}
				}
			}
			
		}
	}
}
