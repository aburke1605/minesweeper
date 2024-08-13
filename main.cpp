#include <SFML/Graphics.hpp>
#include "Game.cpp"
#include <windows.h>

int main() {

	unsigned int x_dimension = 600;
	unsigned int y_dimension = 400;
	sf::RenderWindow window(sf::VideoMode(x_dimension, y_dimension), "window");

	Game game(window);

	// display initial squares
	game.DrawSquares(window);
	window.display();

	while (window.isOpen()) {


		// check for keyboard interaction
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

			if (event.type == sf::Event::MouseButtonPressed) {
				if (event.key.code == sf::Mouse::Left) {
					window.clear(sf::Color::Black); // reset previous frame
					game.DrawSquares(window);
					game.DrawMines(window);
					window.display();
				}
			}
		}
	}

	return 0;
}