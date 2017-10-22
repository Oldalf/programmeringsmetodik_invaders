#include "entity.h"
#include <iostream>

Explosion::Explosion(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	entity(position, size, color, maxVelX), _lifeTime(0) {
	_type = 4;
	_damage = 0;
	_renderPrio = 2;
}

void Explosion::update(entity::entVec &ents, int width, int height, int level) {
	_lifeTime++;
	sf::Color tempCol = _boxObj.getFillColor();
	tempCol.a -= 2;
	_boxObj.setFillColor(tempCol);
	if (_lifeTime >= 122) {
		_active = false;
	}
}

 void Explosion::accelerate(sf::Vector2f newVel, int _level) {
	 _velocity.x = 0;
	 _velocity.y = 0;
}

int Explosion::collide(entity *ent) {
	return 0;
}

void Explosion::onDestroy(entity::entVec &ents) {
	//we do nothing here :)
}