#pragma once
#include "SFML/Window/Keyboard.hpp"
#include <string>
#include <map>
#include <cstdint>
#include <array>

inline constexpr auto DEFAULT_ROM_PATH{ "roms/IBM_Logo.ch8" };

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
