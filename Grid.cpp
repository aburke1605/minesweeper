#include "Square.cpp"
#include <random>

class Grid {
	public:
		Grid(sf::RenderWindow& window, sf::Font* font) {
			sf::Vector2f size(30.0f, 20.0f);
			float width = window.getSize().x / size.x;

			// to randomly position mines
			_generator = std::mt19937(_rd()); // mersenne_twister_engine seeded with rd()
			std::uniform_int_distribution<> distribution(0, 4);

			for (int i = 0; i < (int)size.x; i++) {
				std::vector<Square*> row;
				for (int j = 0; j < (int)size.y; j++) {
					sf::Vector2f position(float(i) * window.getSize().x / size.x, float(j) * window.getSize().y / size.y);
					if (distribution(_generator) == 0) // 20% of the squares are mines
						row.push_back(new Mine(position, width, font));
					else
						row.push_back(new Square(position, width, font));
				}
				_rows_cols.push_back(row);
			}

			// set the number of mines in proximity for each square
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

			// stuff to display when the game ends
			_game_over = false;
			_game_over_text.setFont(*font);
			_game_over_text.setPosition(sf::Vector2f((float)window.getSize().x * 0.25f, (float)window.getSize().y * 0.4f));
			_game_over_text.setString("\
    GAME OVER\n\
play again? (Enter)\
			");
			_game_over_text.setCharacterSize(32);
			_game_over_text.setFillColor(sf::Color::Blue);
			_game_over_text.setStyle(sf::Text::Bold);
		}

		std::vector<std::vector<Square*>>& GetSquares() {
			return _rows_cols;
		}

		bool Update(sf::RenderWindow& window, sf::Event& event) {
			if (event.type == sf::Event::MouseButtonPressed) {
				sf::Vector2i mouse(sf::Mouse::getPosition(window));
				for (unsigned int i = 0; i < (unsigned int)_rows_cols.size(); i++) {
					for (unsigned int j = 0; j < (unsigned int)_rows_cols[i].size(); j++) {
						if (_rows_cols[i][j] == nullptr) // do nothing on already cleared positions anyway
							continue;

						std::pair<sf::Vector2f, sf::Vector2f> edges = _rows_cols[i][j]->GetEdges();

						if (mouse.x > edges.first.x && mouse.x < edges.second.x &&
							mouse.y > edges.first.y && mouse.y < edges.second.y) {

							// left click
							if (event.mouseButton.button == sf::Mouse::Left) {
								if (Mine* mine = dynamic_cast<Mine*>(_rows_cols[i][j])) {
									// reveal all squares
									for (auto& row : _rows_cols) {
										for (auto& square : row) {
											square->Uncover();
										}
									}
									_game_over = true;

									goto draw; // better than break in this case
								}
								else {
									// if the square has zero mines in proximity,
									// then loop over all adjacent squares also flipping them if they have zero and do so recursively
									// stop when the square  has >0 mines in proximity
									if (_rows_cols[i][j]->GetNMinesInProximity() == 0) {
										Clear(i, j);
									}
										_rows_cols[i][j]->Uncover();
								}
							}

							// right click
							else if (event.mouseButton.button == sf::Mouse::Right) {
								_rows_cols[i][j]->FlipFlag();
							}
						}
					}
				}
			}

		draw:
			Draw(window);

			return _game_over;
		}

		void Draw(sf::RenderWindow& window) {
			for (auto& row : _rows_cols) {
				for (auto& square : row) {
					if (square != nullptr)
						square->Draw(window);
				}
			}

			if (_game_over) {
				sf::RectangleShape box(sf::Vector2f((float)window.getSize().x, (float)window.getSize().y));
				box.setFillColor(sf::Color(0, 0, 0, 180));
				window.draw(box);
				window.draw(_game_over_text);
			}
		}

		void Clear(unsigned int i, unsigned int j) {
			_rows_cols[i][j]->Uncover();
			// check surrounding squares
			for (unsigned int m = i - 1; m <= i + 1; m++) {
				if (m < 0 || m >= (unsigned int)_rows_cols.size()) continue; // out of bounds
				for (unsigned int n = j - 1; n <= j + 1; n++) {
					if (n < 0 || n >= (unsigned int)_rows_cols[i].size()) continue; // out of bounds
					if (!(m - i) && !(n - j)) continue; // this square

					// do nothing with mines
					if (dynamic_cast<Mine*>(_rows_cols[m][n]) == nullptr) {
						if (_rows_cols[m][n]->GetNMinesInProximity() == 0 && _rows_cols[m][n]->GetCovered())
							// recursively call
							Clear(m, n);
						else
							// simply uncover squares with >0 mines in proximity
							_rows_cols[m][n]->Uncover();
					}
				}
			}
		}

	private:
		std::vector<std::vector<Square*>> _rows_cols;

		std::random_device _rd; // a seed source for the random number engine
		std::mt19937 _generator;

		bool _game_over;
		sf::Text _game_over_text;
};