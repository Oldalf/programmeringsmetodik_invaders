#include "entity.h"
#include <iostream>

entity::entity(sf::Vector2f position, sf::Vector2f size,sf::Color color, float maxVelX){
	_boxObj.setPosition(position);
	_boxObj.setSize(size);
	_boxObj.setFillColor(color);

	_bot = position.y + size.y; // Bottom left corner
	_left = position.x; // top left corner
	_right = position.x + size.x; // right top corner
	_top = position.y; // top left corner

	_maxVelX = maxVelX;
}

 sf::RectangleShape entity::getRect() const{
	 return _boxObj;
} 

void entity::move() {
	std::cout << "Position before update: " << std::endl;
	std::cout << _boxObj.getPosition().x << "," << _boxObj.getPosition().y << std::endl;

	_boxObj.setPosition(_boxObj.getPosition().x + _velocityX, _boxObj.getPosition().y + _velocityY);

	std::cout << "Position after update: " << std::endl;
	std::cout << _boxObj.getPosition().x << "," << _boxObj.getPosition().y;
}

void entity::accelerate(int x, int y) {
	if (x <= _maxVelX) {
	_velocityX = x;
	}
	_velocityY = y;
}

void entity::update() {

	_bot = _boxObj.getPosition().y + _boxObj.getSize().y;
	_left = _boxObj.getPosition().x;
	_right = _boxObj.getPosition().x + _boxObj.getSize().x;
	_top = _boxObj.getPosition().y;


}

int entity::getPositionX() const{
	return _boxObj.getPosition().x;
}

int entity::getPositionY() const{
	return _boxObj.getPosition().y;
}

/* https://www.youtube.com/watch?v=n0U-NBmLj78i */
