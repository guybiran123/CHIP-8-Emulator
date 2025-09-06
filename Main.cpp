#include <SFML/Graphics.hpp>
#include <iostream>
#include "Memory.h"
#include "Stack.h"
#include "Display.h"
#include "OpcodesFunctions.h"
#include "Constants.h"
#include "TimersHandling.h"

int main(int argc, char* argv[]) {

	std::string rom_path;

	if (argc > 1) {
		rom_path = argv[1]; // ROM path passed as argument
	}
	else {
		rom_path = DEFAULT_ROM_PATH; // default ROM
	}

	Memory memory{ rom_path };
	Stack stack{ };
	Display display{ };
	uint16_t PC{ 512 };
	uint16_t I{ };
	uint8_t delayTimer{ 0 };
	uint8_t soundTimer{ 0 };
	std::mutex delayMTX;
	std::mutex soundMTX;
	std::array<uint8_t, 16> V{ };
	uint16_t opcode{ };

	std::thread t([&]() {
		hadleTimers(delayTimer, soundTimer, delayMTX, soundMTX);
		});
	t.detach();

	while (display.window.isOpen()) {
		sf::Event event;
		while (display.window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				display.window.close();
			}
		}

		opcode = memory.readOpcode(PC);
		switch (opcode >> 12)
		{
		case 0:
			if (opcode == 0x00E0) {
				op00E0_clear(display);
			}
			else if (opcode == 0x00EE) {
				op00EE_return(stack, PC);
			}
			break;
		case 1:
			op1NNN_jump((opcode & 0x0FFF), PC);
			break;
		case 2:
			op2NNN_call(opcode & 0x0FFF, stack, PC);
			break;
		case 3:
			op3XNN_skip(V[(opcode & 0x0F00) >> 8], opcode & 0x00FF, PC);
			break;
		case 4:
			op4XNN_skip(V[(opcode & 0x0F00) >> 8], opcode & 0x00FF, PC);
			break;
		case 5:
			op5XY0_skip(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], PC);
			break;
		case 6:
			op6XNN_set(V[(opcode & 0x0F00) >> 8], opcode & 0x00FF);
			break;
		case 7:
			op7XNN_add(V[(opcode & 0x0F00) >> 8], opcode & 0x00FF);
			break;
		case 8:
			switch (opcode & 0x000F)
			{
			case 0:
				op8XY0_set(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4]);
				break;
			case 1:
				op8XY1_OR(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4]);
				break;
			case 2:
				op8XY2_AND(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4]);
				break;
			case 3:
				op8XY3_XOR(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4]);
				break;
			case 4:
				op8XY4_add(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], V[15]);
				break;
			case 5:
				op8XY5_subtract(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], V[15]);
				break;
			case 6:
				op8XY6_shift(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], V[15]);
				break;
			case 7:
				op8XY7_subtract(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], V[15]);
				break;
			case 0xE:
				op8XYE_shift(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], V[15]);
				break;
			default:
				std::cout << "Something went wrong\n";
				break;
			}
			break;
		case 9:
			op9XY0_skip(V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], PC);
			break;
		case 0xA:
			opANNN_setI(I, opcode & 0x0FFF);
			break;
		case 0xB:
			opBXNN_jumpWithOffset(V[(opcode & 0x0F00) >> 8], opcode & 0x0FFF, PC);
			break;
		case 0xC:
			opCXNN_random(V[(opcode & 0x0F00) >> 8], opcode & 0x00FF);
			break;
		case 0xD:
			opDXYN_display(display, memory, V[(opcode & 0x0F00) >> 8], V[(opcode & 0x00F0) >> 4], opcode & 0x000F, I, V[15]);
			break;
		case 0xE:
			switch (opcode & 0x00FF) {
			case 0x9E:
				opEX9E_skipIfKey(V[(opcode & 0x0F00) >> 8], PC);
				break;
			case 0xA1:
				opEXA1_skipIfKey(V[(opcode & 0x0F00) >> 8], PC);
				break;
			}
			break;
		case 0xF:
			switch (opcode & 0x00FF) {
			case 7:
				opFX07_timer(V[(opcode & 0x0F00) >> 8], delayTimer, delayMTX);
				break;
			case 0x15:
				opFX15_timer(V[(opcode & 0x0F00) >> 8], delayTimer, delayMTX);
				break;
			case 0x18:
				opFX18_timer(V[(opcode & 0x0F00) >> 8], soundTimer, soundMTX);
				break;
			case 0x1E:
				opFX1E_addToIndex(V[(opcode & 0x0F00) >> 8], I, V[15]);
				break;
			case 0x29:
				opFX29_font(V[(opcode & 0x0F00) >> 8], I);
				break;
			case 0x33:
				opFX33_decConversion(memory, V[(opcode & 0x0F00) >> 8], I);
				break;
			case 0x55:
				opFX55_storeMemory(memory, V, (opcode & 0x0F00) >> 8, I);
				break;
			case 0x65:
				opFX65_loadMemory(memory, V, (opcode & 0x0F00) >> 8, I);
				break;
			case 0xA:
				opFX0A_getKey(display, V[(opcode & 0x0F00) >> 8]);
			}
			
			break;
		default:
			std::cout << "Something went wrong\n";
			break;
		}

	}





	return 0;
}



