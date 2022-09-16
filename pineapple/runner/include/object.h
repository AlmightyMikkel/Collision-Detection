#pragma once

#include <SFML/Graphics.hpp>

enum class tag {
	circle,
	line,
	aabb
};

struct line_points {
	sf::Vector2f from, to;
};

class object
{
private:
	sf::Vector2f size;
	sf::Vector2f position;
	sf::Color color;
	sf::FloatRect rect;
	int sections;
	line_points points;
public:
	tag tag;
	object();
	void set_size(float x, float y);
	void set_color(sf::Color _color);
	void set_rect(sf::Vector2f _position, sf::Vector2f _size);
	void set_sections(int _sections);
	void set_position(sf::Vector2f _position);
	void set_points(sf::Vector2f from, sf::Vector2f to);
	sf::Vector2f get_size();
	sf::Color get_color();
	sf::FloatRect get_rect();
	int get_sections();
	sf::Vector2f get_position();
	line_points get_points();
};

