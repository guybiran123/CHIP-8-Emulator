#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System.hpp>
#include <array>
#include <iostream>
#include <windows.h>
#include "Constants.h"



class Display {
private:
	std::array<std::array<uint8_t, 8>, 32> display{};
	

public:
	sf::RenderWindow window;

	Display();

	void clear();

	void turnOnBit(int X, int Y);

	void turnOffBit(int X, int Y);

	bool isBitOn(int X, int Y);

	void updateScreen();
};