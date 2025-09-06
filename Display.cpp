#include "Display.h"

Display::Display() : window{ sf::VideoMode(PIXEL_SIZE * 64, PIXEL_SIZE * 32), "Display" } {
	window.setFramerateLimit(60); 
}

void Display::clear() {
	for (auto& row : display) {
		for (auto& byte : row) {
			byte = 0;
		}
	}
}

void Display::turnOnBit(int X, int Y) {
	display[Y][X / 8] |= (1 << (7 - (X % 8)));
}

void Display::turnOffBit(int X, int Y) {
	display[Y][X / 8] &= ~(1 << (7 - (X % 8)));
}

bool Display::isBitOn(int X, int Y) {
	return (display[Y][X / 8] & (1 << (7 - (X % 8)))) != 0;
}

void Display::updateScreen() {
	
	window.clear(sf::Color::Black); 

	for (int Y = 0; Y < 32; ++Y) {
		for (int X = 0; X < 64; ++X) {
			if (isBitOn(X, Y)) {
				sf::RectangleShape pixel(sf::Vector2f(PIXEL_SIZE, PIXEL_SIZE));
				pixel.setPosition(X * PIXEL_SIZE, Y * PIXEL_SIZE);
				pixel.setFillColor(sf::Color::White);
				window.draw(pixel);
			}
		}
	}

	window.display(); 
}