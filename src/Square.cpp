#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Square {
	public:
		Square(sf::Vector2f position, float size, sf::Font* font) {
			_position = position;
			_edges = std::make_pair(position, position + sf::Vector2f(size, size));

			_rect = sf::RectangleShape(sf::Vector2f(18.0f, 18.0f));
			_rect.setPosition(GetPosition());

			_covered = true;

			_flag = sf::CircleShape(9, 4);
			_flag.setPosition(GetPosition());
			_flag.setFillColor(sf::Color(150, 50, 250));
			_flagged = false;

			_n_mines_in_proximity = 0;

			_text.setFont(*font);
			_text.setPosition(_position + sf::Vector2f(4.0f, 0.0f));
			_text.setString(std::to_string(_n_mines_in_proximity));
			_text.setCharacterSize(15); // in pixels, not points!
			_text.setFillColor(sf::Color::Red);
			_text.setStyle(sf::Text::Bold);
		}

		void Uncover() {
			_covered = false;
		}

		void FlipFlag() {
			_flagged = !_flagged;
		}

		virtual void Draw(sf::RenderWindow& window) const {
			if (_n_mines_in_proximity != 0) {
				window.draw(_text);
			}
			if (_covered) window.draw(_rect);
			if (_flagged) window.draw(_flag);
		}

		void SetNMinesInProximity(unsigned int n_mines_in_proximity) {
			_n_mines_in_proximity = n_mines_in_proximity;
			_text.setString(std::to_string(_n_mines_in_proximity));
		}

		sf::Vector2f GetPosition() const {
			return _position;
		}
		std::pair< sf::Vector2f, sf::Vector2f> GetEdges() const {
			return _edges;
		}

		bool GetCovered() {
			return _covered;
		}

		unsigned int GetNMinesInProximity() const {
			return _n_mines_in_proximity;
		}

	private:
		sf::Vector2f _position;
		std::pair<sf::Vector2f, sf::Vector2f> _edges;

		sf::RectangleShape _rect;
		sf::CircleShape _flag;
		bool _covered;
		bool _flagged;
		unsigned int _n_mines_in_proximity;

		sf::Text _text;
};



class Mine : public Square {
	public:
		Mine(sf::Vector2f position, float size, sf::Font* font) : Square(position, size, font) {
			//_detonated = false;

			_mine = sf::CircleShape(9, 8);
			_mine.setPosition(GetPosition());
			_mine.setFillColor(sf::Color(100, 100, 100));
		}

		void Draw(sf::RenderWindow& window) const {
			window.draw(_mine);
			Square::Draw(window);
		}

	private:
		sf::CircleShape _mine;
};