#include "object.h"


object::object()
{

}

void object::set_size(float x, float y) {
	this->size = { x,y };
}

void object::set_color(sf::Color _color) {
	this->color = _color;
}

void object::set_rect(sf::Vector2f _position, sf::Vector2f _size) {
	sf::Vector2f adjusted_position = { _position.x - (_size.x / 2), _position.y - (_size.y / 2)};
	this->rect = { _position, _size};
}

void object::set_sections(int _sections) {
	this->sections = _sections;
}

void object::set_position(sf::Vector2f _position) {
	this->position = { _position.x, _position.y };
}

void object::set_points(sf::Vector2f from, sf::Vector2f to) {
	this->points = { from, to };	
}

sf::Vector2f object::get_size() {
	return this->size;
}

sf::Color object::get_color() {
	return this-> color;
}

sf::FloatRect object::get_rect() {
	return this->rect;
}

int object::get_sections() {
	return this->sections;
}
sf::Vector2f object::get_position() {
	return this->position;
}

line_points object::get_points() {
	return this->points;
}