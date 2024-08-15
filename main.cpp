#include <SFML/Graphics.hpp>
#include "Game.cpp"
#include <windows.h>

int main() {

	unsigned int x_dimension = 600;
	unsigned int y_dimension = 400;
	sf::RenderWindow window(sf::VideoMode(x_dimension, y_dimension), "window");

	/*Game game(window);

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

					std::cout << sf::Mouse::getPosition(window).x << "," << sf::Mouse::getPosition(window).y << std::endl;
					auto coordinates = game.GetBoundaries();
					auto squares = game.GetSquares();
					size_t col, row;
					for (size_t i = 0; i < coordinates.size(); i++) {
						for (size_t j = 0; j < coordinates[i].size(); j++) {
							if (sf::Mouse::getPosition(window).x > coordinates[i][j].first.x &&
								sf::Mouse::getPosition(window).x < coordinates[i][j].second.x &&
								sf::Mouse::getPosition(window).y > coordinates[i][j].first.y &&
								sf::Mouse::getPosition(window).y < coordinates[i][j].second.y)
							{
								std::cout << "(" << coordinates[i][j].first.x << "," << coordinates[i][j].second.x << "),  " << "(" << coordinates[i][j].first.y << "," << coordinates[i][j].second.y << ")\n";
								std::cout << RemoveSquare(squares, coordinates[i][j].first) << std::endl;
							}

						}
					}

					window.clear(sf::Color::Black); // reset previous frame
					game.DrawSquares(window);
					game.DrawMines(window);
					window.display();
				}
			}
		}
	}*/

	return 0;
}