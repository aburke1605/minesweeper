#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>



#include <iostream>

class Square {
	public:
		Square(sf::Vector2f position, float size) {
			_position = position;
			_edges = std::make_pair(position, position + sf::Vector2f(size, size));

			_rect = sf::RectangleShape(sf::Vector2f(18.0f, 18.0f));
			_rect.setPosition(GetPosition());

			_flag = sf::CircleShape(9, 4);
			_flag.setPosition(GetPosition());
			_flag.setFillColor(sf::Color(150, 50, 250));
			_flagged = false;

			_n_mines_in_proximity = 0;
		}

		void FlipFlag() {
			_flagged = !_flagged;
		}

		virtual void Draw(sf::RenderWindow& window) const {
			window.draw(_rect);
			if (_flagged)
				window.draw(_flag);
		}


		sf::Vector2f GetPosition() const {
			return _position;
		}
		std::pair< sf::Vector2f, sf::Vector2f> GetEdges() const {
			return _edges;
		}

	private:
		sf::Vector2f _position;
		std::pair<sf::Vector2f, sf::Vector2f> _edges;

		sf::RectangleShape _rect;
		sf::CircleShape _flag;
		bool _flagged;
		unsigned int _n_mines_in_proximity;
};



class Mine : public Square {
	public:
		Mine(sf::Vector2f position, float size) : Square(position, size) {
			_detonated = false;

			_mine = sf::CircleShape(5, 8);
			_mine.setPosition(GetPosition());
			_mine.setFillColor(sf::Color(100, 100, 100));
		}
		void Draw(sf::RenderWindow& window) const {
			if (!_detonated)
				Square::Draw(window);
			window.draw(_mine); // reverse these later
		}

	private:
		bool _detonated;
		sf::CircleShape _mine;
};