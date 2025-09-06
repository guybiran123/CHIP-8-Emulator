#pragma once
#include "SFML/Window/Keyboard.hpp"
#include <cstdint>
#include <ctime>
#include <cstdlib>
#include <mutex>
#include "Stack.h"
#include "Display.h"
#include "Memory.h"
#include "Random_mt.h"
#include "Constants.h"

void op00E0_clear(Display& display);

void op00EE_return(Stack& stack, uint16_t& PC);

void op1NNN_jump(uint16_t NNN, uint16_t& PC);

void op2NNN_call(uint16_t NNN, Stack& stack, uint16_t& PC);

void op3XNN_skip(uint8_t VX, uint8_t NN, uint16_t& PC);

void op4XNN_skip(uint8_t VX, uint8_t NN, uint16_t& PC);

void op5XY0_skip(uint8_t VX, uint8_t VY, uint16_t& PC);

void op6XNN_set(uint8_t& VX, uint8_t NN);

void op7XNN_add(uint8_t& VX, uint8_t NN);

void op8XY0_set(uint8_t& VX, uint8_t VY);

void op8XY1_OR(uint8_t& VX, uint8_t VY);

void op8XY2_AND(uint8_t& VX, uint8_t VY);

void op8XY3_XOR(uint8_t& VX, uint8_t VY);

void op8XY4_add(uint8_t& VX, uint8_t VY, uint8_t& VF);

void op8XY5_subtract(uint8_t& VX, uint8_t VY, uint8_t& VF);

void op8XY6_shift(uint8_t& VX, uint8_t VY, uint8_t& VF);

void op8XY7_subtract(uint8_t& VX, uint8_t VY, uint8_t& VF);

void op8XYE_shift(uint8_t& VX, uint8_t VY, uint8_t& VF);

void op9XY0_skip(uint8_t VX, uint8_t VY, uint16_t& PC);

void opANNN_setI(uint16_t& I, uint16_t NNN);

void opBXNN_jumpWithOffset(uint8_t VX, uint16_t XNN, uint16_t& PC);

void opCXNN_random(uint8_t& VX, uint8_t NN);

void opDXYN_display(Display& display, Memory& memory, uint8_t VX, uint8_t VY, uint8_t N, uint16_t I, uint8_t& VF);

void opEX9E_skipIfKey(uint8_t VX, uint16_t& PC);

void opEXA1_skipIfKey(uint8_t VX, uint16_t& PC);

void opFX07_timer(uint8_t& VX, uint8_t delayTimer, std::mutex& mtx);

void opFX15_timer(uint8_t VX, uint8_t& delayTimer, std::mutex& mtx);

void opFX18_timer(uint8_t VX, uint8_t& soundTimer, std::mutex& mtx);

void opFX1E_addToIndex(uint8_t VX, uint16_t& I, uint8_t& VF);

void opFX29_font(uint8_t VX, uint16_t& I);

void opFX33_decConversion(Memory& memory, uint8_t VX, uint16_t I);

void opFX55_storeMemory(Memory& memory, const std::array<uint8_t, 16>& V, uint8_t X, uint16_t I);

void opFX65_loadMemory(const Memory& memory, std::array<uint8_t, 16>& V, uint8_t X, uint16_t I);

void opFX0A_getKey(Display& display, uint8_t& VX);