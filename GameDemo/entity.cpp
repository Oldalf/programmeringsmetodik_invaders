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
	/* std::cout << "Velocity f�re udpdate: " << std::endl;
	std::cout << _velocity.x << "," << _velocity.y << std::endl; */

	_boxObj.setPosition(_boxObj.getPosition().x + _velocity.x, _boxObj.getPosition().y + _velocity.y);

	/* std::cout << "Velocity efter udpdate: " << std::endl;
	std::cout << _velocity.x << "," << _velocity.y << std::endl; */
}

void entity::accelerate(sf::Vector2f newVel) {

	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
	_velocity.x = newVel.x;
	}
	_velocity.y = newVel.y;
}

/* https://www.youtube.com/watch?v=n0U-NBmLj78i */
bool entity::collision(entity *ent){
	if (_boxObj.getPosition().x > ent->getRect()->getPosition().x + ent->getRect()->getSize().x || // min v�nster st�rra �n deras h�ger 
		_boxObj.getPosition().y > ent->getRect()->getPosition().y + ent->getRect()->getSize().y || // min top st�rre �n deras bot.
		_boxObj.getPosition().x + _boxObj.getSize().x < ent->getRect()->getPosition().x || // min h�ger mindre �n deras v�nster
		_boxObj.getPosition().y + _boxObj.getSize().y < ent->getRect()->getPosition().y // min bot mindre �n deras top
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

Lazer::Lazer(sf::Vector2f position, sf::Vector2f size,sf::Color color, float maxVelX):
	entity(position, size, color, maxVelX) {
	_type = 2; 
	
}

int Lazer::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit == true && ent->getType() == 1) {
		return 1; // it's a hit and the updater will have to cover it
	}
	return 0;
}

/*
*************************************************
********************  Bombs  ********************
*************************************************
*/

Bomb::Bomb(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX):
	entity(position, size, color, maxVelX) {
	_type = 3;
}

int Bomb::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit == true && ent->getType() == 0) {
		return 1; // it's a hit and the updater will have to cover it
	}
	return 0;
}

void Bomb::accelerate(sf::Vector2f newVel) {
	accelerate(newVel, 1);
}

void Bomb::accelerate(sf::Vector2f newVel, int level) {
	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
		_velocity.x = newVel.x + (level / 2);
	}
	_velocity.y = newVel.y;
}