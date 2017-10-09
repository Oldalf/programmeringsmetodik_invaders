#include "Alien.h"

Alien::Alien(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	entity(position, size, color, maxVelX) {
	_type = 1;
}

int Alien::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit == true && ent->getType() == 2) {
		return 1; // it's a hit and the updater will have to cover it
	}
	return 0;
}

void Alien::accelerate(sf::Vector2f newVel) {
	accelerate(newVel, 1);
}

void Alien::accelerate(sf::Vector2f newVel, int level) {
	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
		_velocity.x = newVel.x + (level / 2);
	}
	_velocity.y = newVel.y;
}

void Alien::setActive(bool b) {
	_active = b;
}

bool Alien::active() const {
	return _active;
}
