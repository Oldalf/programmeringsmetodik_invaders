#include "entity.h"

Lazer::Lazer(sf::Vector2f position, sf::Vector2f size,sf::Color color, float maxVelX) :
	entity(position, size, color, maxVelX) {
	_type = 2;
	_damage = 1;
	_renderPrio = 0;
}

void Lazer::update(entity::entVec &ents,int width, int height, int level) {
		
	_boxObj.setPosition(_boxObj.getPosition().x + _velocity.x, _boxObj.getPosition().y + _velocity.y);

	/* Lazer movement logic */
	if (_boxObj.getPosition().x + _boxObj.getSize().x > width) {
		_boxObj.setPosition(sf::Vector2f(
		width - _boxObj.getSize().x, _boxObj.getSize().y
		));
	}

	if (_boxObj.getPosition().x < 0) {
		_boxObj.setPosition(sf::Vector2f(
		0, _boxObj.getSize().y
		));
	}

	if (_boxObj.getPosition().y < 0) {
		accelerate(sf::Vector2f(0, 0));
		_active = false;
	}
}

void Lazer::accelerate(sf::Vector2f newVel, int level) {
	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
		_velocity.x = newVel.x;
	}
	_velocity.y = newVel.y;
}

int Lazer::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit == true && ent->getType() == 1) {
		ent->setActive(false);
		_active = false;
		return 1; // it's a hit and the updater will have to cover it
	}
	return 0;
}