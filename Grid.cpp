#include "Square.cpp"
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

			// set number of mines in proximity for each square
			for (int i = 0; i < (int)_rows_cols.size(); i++) {
				for (int j = 0; j < (int)_rows_cols[i].size(); j++) {

					// for this square, look in the surrounding 8 squares
					unsigned int n_mines_in_proximity = 0;

					for (int m = i - 1; m <= i + 1; m++) {
						if (m < 0 || m >= (int)_rows_cols.size()) continue; // out of bounds
						for (int n = j - 1; n <= j + 1; n++) {
							if (n < 0 || n >= (int)_rows_cols[i].size()) continue; // out of bounds
							if (!(m - i) && !(n - j)) continue; // this square
							
							if (Mine* mine = dynamic_cast<Mine*>(_rows_cols[m][n]))
								n_mines_in_proximity++;
						}
					}
					_rows_cols[i][j]->SetNMinesInProximity(n_mines_in_proximity);
				}
			}
		}

		std::vector<std::vector<Square*>>& GetSquares() {
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