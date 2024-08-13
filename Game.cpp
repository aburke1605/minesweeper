#include <SFML/Graphics.hpp>
#include <vector>
#include <iostream>
#include <time.h>
#include <stdlib.h>

class Game {
	public:
		Game(sf::RenderWindow& window) {
			_size = sf::Vector2u(30, 20);
			_cell_size = 0.9f;
			_n_mines = 100;

			for (unsigned int i = 0; i < _size.x; i++) {
				std::vector <std::pair<sf::Vector2f, sf::Vector2f>> col_i_boundaries;
				std::vector<sf::Vector2f> col_i;
				for (unsigned int j = 0; j < _size.y; j++) {
					sf::Vector2f low_boundary((float)(i * window.getSize().x / _size.x), (float)(j * window.getSize().y / _size.y));
					sf::Vector2f high_boundary((float)((i + 1) * window.getSize().x / _size.x), (float)((j + 1) * window.getSize().y / _size.y));
					col_i_boundaries.push_back(std::make_pair(low_boundary, high_boundary));
					//col_i.push_back(sf::Vector2f((float)(i * window.getSize().x / _size.x), (float)(j * window.getSize().y / _size.y)));
					col_i.push_back(low_boundary);
				}
				_coordinate_boundaries.push_back(col_i_boundaries);
				_squares.push_back(col_i);
			}

			srand((unsigned int)time(NULL));
			for (unsigned int i = 0; i < _n_mines; i++) {
				unsigned int x = rand() % _size.x;
				unsigned int y = rand() % _size.y;
				sf::RectangleShape mine(sf::Vector2f((float)window.getSize().x / _size.x * _cell_size, (float)window.getSize().y / _size.y * _cell_size));
				mine.setPosition(sf::Vector2f((float)(x * window.getSize().x / _size.x), (float)(y * window.getSize().y / _size.y)) + sf::Vector2f(_size.x * (1.0f - _cell_size) / 2, _size.y * (1.0f - _cell_size) / 2));
				mine.setFillColor(sf::Color(0, 0, 0));
				_mines.push_back(mine);
			}
		}

		std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>> GetBoundaries() const {
			return _coordinate_boundaries;
		}

		void DrawSquares(sf::RenderWindow& window) {
			// TODO copy DrawMines
			sf::RectangleShape rect(sf::Vector2f((float)window.getSize().x / _size.x * _cell_size, (float)window.getSize().y / _size.y * _cell_size));

			for (auto& col : _squares) {
				for (auto& col_row : col) {
					rect.setPosition(col_row + sf::Vector2f(_size.x * (1.0f - _cell_size) / 2, _size.y * (1.0f - _cell_size) / 2));
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
		std::vector<std::vector<std::pair<sf::Vector2f, sf::Vector2f>>> _coordinate_boundaries;
		std::vector<sf::RectangleShape> _mines;
};