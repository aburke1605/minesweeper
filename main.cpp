#include <SFML/Graphics.hpp>
#include "Grid.cpp"
#include <windows.h>
#include <iostream>

int main() {

	unsigned int x_dimension = 600;
	unsigned int y_dimension = 400;
	sf::RenderWindow window(sf::VideoMode(x_dimension, y_dimension), "window");

	Grid grid(window);

	// display initial squares
	grid.Draw(window);
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
					for (auto& row : grid.GetPoints()) {
						for (auto& point : row) {
							if (point == nullptr)
								continue;
							std::pair<sf::Vector2f, sf::Vector2f> edges = point->GetEdges();
							if (
							sf::Mouse::getPosition(window).x > edges.first.x &&
							sf::Mouse::getPosition(window).x < edges.second.x &&
							sf::Mouse::getPosition(window).y > edges.first.y &&
							sf::Mouse::getPosition(window).y < edges.second.y) {
								std::cout << "(" << edges.first.x << "," << edges.second.x << "),  " << "(" << edges.first.y << "," << edges.second.y << ")\n";
								point = nullptr;
							}

						}
					}

					window.clear(sf::Color::Black); // reset previous frame
					grid.Draw(window);
					window.display();
				}
			}
		}
	}

	return 0;
}