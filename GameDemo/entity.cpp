#include "entity.h"
#include <iostream>

/*
*************************************************
********************  Entity ********************
*************************************************
*/

entity::entity(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	_velocity() {
	_boxObj.setPosition(position);
	_boxObj.setSize(size);
	_boxObj.setFillColor(color);
	_maxVelX = maxVelX;
}

entity::~entity() {}

void entity::move() {
	/* std::cout << "Velocity före udpdate: " << std::endl;
	std::cout << _velocity.x << "," << _velocity.y << std::endl; */

	_boxObj.setPosition(_boxObj.getPosition().x + _velocity.x, _boxObj.getPosition().y + _velocity.y);

	_velocity.x = 0;
	_velocity.y = 0;

	/* std::cout << "Velocity efter udpdate: " << std::endl;
	std::cout << _velocity.x << "," << _velocity.y << std::endl; */
}

void entity::accelerate(sf::Vector2f newVel) {

	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
	_velocity.x =+ newVel.x;
	}
	_velocity.y =+ newVel.y;
}

/* https://www.youtube.com/watch?v=n0U-NBmLj78i */
bool entity::collision(entity *ent){
	if (_boxObj.getPosition().x > ent->getRect()->getPosition().x + ent->getRect()->getSize().x || // min vänster störra än deras höger 
		_boxObj.getPosition().y > ent->getRect()->getPosition().y + ent->getRect()->getSize().y || // min top större än deras bot.
		_boxObj.getPosition().x + _boxObj.getSize().x < ent->getRect()->getPosition().x || // min höger mindre än deras vänster
		_boxObj.getPosition().y + _boxObj.getSize().y < ent->getRect()->getPosition().y // min bot mindre än deras top
		) {
	return false;
	}
	return true;
}

sf::Vector2f entity::getPosition() const{
	return _boxObj.getPosition();
}

int entity::getType() const {
	return _type;
}

/* Man kan inte returnera konstanta pekare, headsup/fix. */
sf::RectangleShape* entity::getRect(){
	 return &_boxObj;
}

sf::Vector2f entity::getVelocity() const {
	return _velocity;
}

void entity::setSize(sf::Vector2f size) {
	_boxObj.setSize(size);
}

void entity::setColor(sf::Color color) {
	_boxObj.setFillColor(color);
}

void entity::setPosition(sf::Vector2f position) {
	_boxObj.setPosition(position);
}

/*
*************************************************
********************  Lazer  ********************
*************************************************
*/

/*
*************************************************
********************  Bombs  ********************
*************************************************
*/