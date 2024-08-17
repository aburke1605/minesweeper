#include <SFML/Graphics.hpp>
#include "Grid.cpp"
#ifdef _WIN32
#include <windows.h>
void s() {
	Sleep(5000);
}
#elif __linux__
#include <unistd.h>  // For POSIX functions on Linux
void s() {
	sleep(5);
}
#else
#error "Unknown operating system"
#endif
#include <iostream>

int main() {

	unsigned int x_dimension = 600;
	unsigned int y_dimension = 400;
	sf::RenderWindow window(sf::VideoMode(x_dimension, y_dimension), "window");

	Grid grid(window);

	// display initial squares
	grid.Draw(window);
	window.display();

	bool game_over = false;
	while (window.isOpen() && !game_over) {


		// check for keyboard interaction
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

			game_over = grid.Update(window, event);
		}
	}

	s(); // ms
	return 0;
}