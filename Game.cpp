#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

class Game {
	public:
		Game(sf::RenderWindow& window) {
			_size = sf::Vector2u(30, 20);
			_cell_size = 0.9;
			_n_mines = 100;

			for (unsigned int i = 0; i < _size.x; i++) {
				std::vector<sf::Vector2f> row_i;
				for (unsigned int j = 0; j < _size.y; j++) {
					row_i.push_back(sf::Vector2f((float)(i * window.getSize().x / _size.x), (float)(j * window.getSize().y / _size.y)));
				}
				_squares.push_back(row_i);
			}

			//DrawSquares(window);

			srand(time(NULL));
			for (unsigned int i = 0; i < _n_mines; i++) {
				unsigned int x = rand() % _size.x;
				unsigned int y = rand() % _size.y;
				sf::RectangleShape mine(sf::Vector2f((float)window.getSize().x / _size.x * _cell_size, (float)window.getSize().y / _size.y * _cell_size));
				mine.setPosition(sf::Vector2f((float)(x * window.getSize().x / _size.x), (float)(y * window.getSize().y / _size.y)) + sf::Vector2f(_size.x * (1.0f - _cell_size) / 2, _size.y * (1.0f - _cell_size) / 2));
				mine.setFillColor(sf::Color(0, 0, 0));
				_mines.push_back(mine);
			}
		}

		void DrawSquares(sf::RenderWindow& window) {
			sf::RectangleShape rect(sf::Vector2f((float)window.getSize().x / _size.x * _cell_size, (float)window.getSize().y / _size.y * _cell_size));

			for (auto& row : _squares) {
				for (auto& row_col : row) {
					rect.setPosition(row_col + sf::Vector2f(_size.x * (1.0f - _cell_size) / 2, _size.y * (1.0f - _cell_size) / 2));
					window.draw(rect);
				}
			}
		}

		void DrawMines(sf::RenderWindow& window) {
			for (auto& mine : _mines) {
				window.draw(mine);
			}
		}

	private:
		sf::Vector2u _size;
		float _cell_size;
		unsigned int _n_mines;
		std::vector<std::vector<sf::Vector2f>> _squares;
		std::vector<sf::RectangleShape> _mines;
};