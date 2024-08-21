#include <SFML/Graphics.hpp>
#include "Grid.cpp"

/* TODO:
* way to determine if all unmined squares have been uncovered
* reveal all mines when win or lose
* ensure first click is a square with no mines in proximity
*/


int main() {

	unsigned int x_dimension = 600;
	unsigned int y_dimension = 400;
	sf::RenderWindow window(sf::VideoMode(x_dimension, y_dimension), "window");

	sf::Font* font = new sf::Font;
	if (!font->loadFromFile("arial.ttf")) {
		return EXIT_FAILURE;
	}

	Grid grid(window, font);

	// display initial squares
	grid.Draw(window);
	window.display();

	while (window.isOpen()) {

		bool game_over = false;

		// check for keyboard interaction
		sf::Event event;
		while (window.pollEvent(event)) {

			if (event.type == sf::Event::Closed || (event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))
				window.close();

			window.clear(sf::Color::Black); // reset previous frame
			game_over = grid.Update(window, event);
			window.display();

			if (game_over) {
				while (1) { // could probably be neater
					while (window.pollEvent(event)) {
						if (event.type == sf::Event::KeyPressed) {
							if (event.key.code == sf::Keyboard::Enter) {
								window.close();
								return main();
							}
							else if (event.key.code == sf::Keyboard::Escape) {
								return 0;
							}
						}
					}
				}
			}
		}
	}
}