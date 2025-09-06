#pragma once
#include "SFML/Window/Keyboard.hpp"
#include <string>
#include <map>
#include <cstdint>
#include <array>


//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\source\\repos\\Chip-8\\IBM Logo.ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\source\\repos\\Chip-8\\test_opcode.ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\source\\repos\\Chip-8\\delay_timer_test.ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\source\\repos\\Chip-8\\cavern.ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\source\\repos\\Chip-8\\Pong (alt).ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\Downloads\\program.c8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\Downloads\\MostDangerousGame.ch8" };
inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\Downloads\\Puzzle.ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\Downloads\\Space Flight.ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\Downloads\\Blitz [David Winter].ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\Downloads\\Connect4.ch8" };
//inline constexpr auto EXECUTION_FILE_PATH{ "C:\\Users\\guybi\\Downloads\\X-Mirror.ch8" };





inline constexpr int PIXEL_SIZE{ 14 };

inline constexpr std::array<sf::Keyboard::Key, 16> KEYS{
	sf::Keyboard::X,
	sf::Keyboard::Num1,
	sf::Keyboard::Num2,
	sf::Keyboard::Num3,
	sf::Keyboard::Q,
	sf::Keyboard::W,
	sf::Keyboard::E,
	sf::Keyboard::A,
	sf::Keyboard::S,
	sf::Keyboard::D,
	sf::Keyboard::Z,
	sf::Keyboard::C,
	sf::Keyboard::Num4,
	sf::Keyboard::R,
	sf::Keyboard::F,
	sf::Keyboard::V,
	
};
