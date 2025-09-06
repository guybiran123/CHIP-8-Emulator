#include "TimersHandling.h"

void hadleTimers(uint8_t& delayTimer, uint8_t& soundTimer, std::mutex& delayMTX, std::mutex& soundMTX) {
	while (true) {
		if (delayTimer > 0) {
			delayMTX.lock();
			--delayTimer;
			delayMTX.unlock();
		}
		if (soundTimer > 0) {
			soundMTX.lock();
			--soundTimer;
			soundMTX.unlock();
			Beep(1000, 20);
		}
		std::this_thread::sleep_for(std::chrono::milliseconds(1000 / 60));
	}
	
}