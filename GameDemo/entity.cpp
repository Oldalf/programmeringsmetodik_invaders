#include "entity.h"
#include <iostream>

/*
*************************************************
********************  Entity ********************
*************************************************
*/

entity::entity(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	_maxVelX(maxVelX), _velocity(), _active(true),_type() {
	_boxObj.setPosition(position);
	_boxObj.setSize(size);
	_boxObj.setFillColor(color);
	_renderPrio = 0;
}

entity::~entity() {}

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


sf::Vector2f entity::getPosition() const {
	return _boxObj.getPosition();
}

int entity::getType() const {
	return _type;
}

int entity::getDamage() const {
	return _damage;
}

int entity::getRenderPrio() const {
	return _renderPrio;
}

bool entity::active() const {
	return _active;
}

sf::RectangleShape* entity::getRect() {
	return &_boxObj;
}

sf::Vector2f entity::getVelocity() const {
	return _velocity;
}

void entity::setActive(bool newAct) {
	_active = newAct;
}

void entity::setSize(sf::Vector2f size) {
	_boxObj.setSize(size);
}

void entity::setPosition(sf::Vector2f position) {
	_boxObj.setPosition(position);
}

void entity::setColor(sf::Color color) {
	_boxObj.setFillColor(color);
}

void entity::setRenderPrio(int prio) {
	_renderPrio = prio;
}

void entity::onDestroy(entity::entVec &ents) {
	// Not needed but some subclasses might want this.
}