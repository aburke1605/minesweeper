#include "Point.cpp"
#include <random>

class Grid {
	public:
		Grid(sf::RenderWindow& window) {
			sf::Vector2f size(30.0f, 20.0f);
			float width = window.getSize().x / size.x;

			_generator = std::mt19937(_rd()); // mersenne_twister_engine seeded with rd()
			std::uniform_int_distribution<> distribution(0, 4);

			for (int i = 0; i < (int)size.x; i++) {
				std::vector<Square*> row;
				for (int j = 0; j < (int)size.y; j++) {
					sf::Vector2f position(float(i) * window.getSize().x / size.x, float(j) * window.getSize().y / size.y);
					if (distribution(_generator) == 0) // 20% of the squares are mines
						row.push_back(new Mine(position, width));
					else
						row.push_back(new Square(position, width));
				}
				_rows_cols.push_back(row);
			}
		}

		std::vector<std::vector<Square*>>& GetPoints() {
			return _rows_cols;
		}

		void Draw(sf::RenderWindow& window) {
			for (auto& row : _rows_cols) {
				for (auto& square : row) {
					if (square != nullptr)
						square->Draw(window);
				}
			}
		}

	private:
		std::vector<std::vector<Square*>> _rows_cols;

		std::random_device _rd; // a seed source for the random number engine
		std::mt19937 _generator;
};