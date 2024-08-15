#include "Point.cpp"

class Grid {
public:
	Grid(sf::RenderWindow& window) {
		sf::Vector2f size(30.0f, 20.0f);
		float width = window.getSize().x / size.x;


		for (int i = 0; i < (int)size.x; i++) {
			std::vector<Point*> row;
			for (int j = 0; j < (int)size.y; j++) {
				sf::Vector2f position(float(i) * window.getSize().x / size.x, float(j) * window.getSize().y / size.y);
				row.push_back(new Square(position, width));
			}
			_rows_cols.push_back(row);
		}
	}

	std::vector<std::vector<Point*>>& GetPoints() {
		return _rows_cols;
	}

	void Draw(sf::RenderWindow& window) {
		for (auto& row : _rows_cols) {
			for (auto& point : row) {
				if (point != nullptr)
					point->Draw(window);
			}
		}
	}

private:
	std::vector<std::vector<Point*>> _rows_cols;
};