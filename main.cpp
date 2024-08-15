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
				sf::Vector2i mouse(sf::Mouse::getPosition(window));
				for (auto& row : grid.GetPoints()) {
					for (auto& point : row) {
						if (point == nullptr) // do nothing on already cleared positions anyway
							continue;

						std::pair<sf::Vector2f, sf::Vector2f> edges = point->GetEdges();

						if (mouse.x > edges.first.x && mouse.x < edges.second.x &&
							mouse.y > edges.first.y && mouse.y < edges.second.y) {

							// left click
							if (event.key.code == sf::Mouse::Left) {
									point = nullptr;
							}

							// right click
							else if (event.key.code == sf::Mouse::Right) {
								point->FlipFlag();
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