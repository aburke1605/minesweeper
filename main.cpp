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

			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mouse(sf::Mouse::getPosition(window));
				for (auto& row : grid.GetSquares()) {
					for (auto& square : row) {
						if (square == nullptr) // do nothing on already cleared positions anyway
							continue;

						std::pair<sf::Vector2f, sf::Vector2f> edges = square->GetEdges();

						if (mouse.x > edges.first.x && mouse.x < edges.second.x &&
							mouse.y > edges.first.y && mouse.y < edges.second.y) {

							// left click
							if (event.mouseButton.button == sf::Mouse::Left) {
								if (Mine* mine = dynamic_cast<Mine*>(square)) {
									mine->Detonate();
									game_over = true;
								}
								else {
									square = nullptr;
								}
							}

							// right click
							else if (event.mouseButton.button == sf::Mouse::Right) {
								square->FlipFlag();
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

	s(); // ms
	return 0;
}