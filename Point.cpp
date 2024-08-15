#include <SFML/System.hpp>
#include <SFML/Graphics.hpp>

class Point {
	public:
		Point(sf::Vector2f position, float size) {
			_position = position;
			_edges = std::make_pair(position, position + sf::Vector2f(size, size));
		}
		sf::Vector2f GetPosition() const {
			return _position;
		}
		std::pair< sf::Vector2f, sf::Vector2f> GetEdges() const {
			return _edges;
		}
		virtual void Draw(sf::RenderWindow& window) const {}
	private:
		sf::Vector2f _position;
		std::pair<sf::Vector2f, sf::Vector2f> _edges;
};



class Square : public Point {
	public:
		Square(sf::Vector2f position, float size) : Point(position, size) {
			_rect = sf::RectangleShape(sf::Vector2f(19.0f, 19.0f));
			_rect.setPosition(GetPosition());
			_flagged = false;
			_n_mines_in_proximity = 0;
		}
		void Draw(sf::RenderWindow& window) const {
			window.draw(_rect);
		}
	private:
		sf::RectangleShape _rect;
		bool _flagged;
		unsigned int _n_mines_in_proximity;
};



class Mine : public Point {
	public:
		Mine(sf::Vector2f position, float size) : Point(position, size) {}
		void Draw() const {

		}
};