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

			_covered = true;

			_flag = sf::CircleShape(9, 4);
			_flag.setPosition(GetPosition());
			_flag.setFillColor(sf::Color(150, 50, 250));
			_flagged = false;

			_n_mines_in_proximity = 0;


			if (!_font.loadFromFile("arial.ttf")) {}
			_text.setFont(_font);
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

			if (_n_mines_in_proximity != 0) {// reverse these later^
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

		sf::Font _font; // this should be shared between all instances
		sf::Text _text;
};



class Mine : public Square {
	public:
		Mine(sf::Vector2f position, float size) : Square(position, size) {
			_detonated = false;

			_mine = sf::CircleShape(7, 8); // make this (9, 8)
			_mine.setPosition(GetPosition());
			_mine.setFillColor(sf::Color(100, 100, 100));
		}

		void Detonate() {
			_detonated = true;
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