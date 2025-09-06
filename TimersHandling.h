#pragma once
#include <cstdint>
#include <mutex>
#include <chrono>
#include <Windows.h>

void hadleTimers(uint8_t& delayTimer, uint8_t& soundTimer, std::mutex& delayMTX, std::mutex& soundMTX);

