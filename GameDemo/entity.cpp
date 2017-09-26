#include "entity.h"
#include <iostream>

entity::entity(sf::Vector2f position, sf::Vector2f size,sf::Color color, float maxVelX){
	_boxObj.setPosition(position);
	_boxObj.setSize(size);
	_boxObj.setFillColor(color);
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

int entity::getPositionX() const{
	return _boxObj.getPosition().x;
}

int entity::getPositionY() const{
	return _boxObj.getPosition().y;
}

void entity::setSize(sf::Vector2f size) {
	_boxObj.setSize(size);
}

void entity::setColor(sf::Color color) {
	_boxObj.setFillColor(color);
}

/* https://www.youtube.com/watch?v=n0U-NBmLj78i */
