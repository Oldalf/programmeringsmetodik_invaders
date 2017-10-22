#include "entity.h"

Bomb::Bomb(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	entity(position, size, color, maxVelX) {
	_type = 3;
	_damage = 5;
	_renderPrio = 0;
}

void Bomb::update(entity::entVec &ents, int width, int height, int level) {
	_boxObj.setPosition(_boxObj.getPosition().x + _velocity.x, _boxObj.getPosition().y + _velocity.y);

	/* bomb movement logic */
	if (_boxObj.getPosition().x + _boxObj.getSize().x > width) {
		accelerate(sf::Vector2f(-2, _velocity.y), level);
	}

	if (_boxObj.getPosition().x < 0) {
		accelerate(sf::Vector2f(2, _velocity.y), level);
	}

	if (_boxObj.getPosition().y > height) {
		accelerate(sf::Vector2f(0, 0));
		_active = false;
	}
}

void Bomb::accelerate(sf::Vector2f newVel, int level) {
	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
		if (newVel.x > 0) {
			_velocity.x = newVel.x + (level / 3);
		}
		else {
			_velocity.x = newVel.x - (level / 3);
		}
	}
	_velocity.y = newVel.y + (level / 3);
}

int Bomb::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit == true && ent->getType() == 0) {
		return 1; // it's a hit and the updater will have to cover it
	}
	return 0;

}