#include "entity.h"
#include <iostream>

Alien::Alien(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	entity(position, size, color, maxVelX), _alienClock(), _lastFire(_alienClock.getElapsedTime()) {
	_type = 1;
	_damage = 10;
	_renderPrio = 0;
}

void Alien::update(entVec &ents, int width, int height, int level) {

	_boxObj.setPosition(_boxObj.getPosition().x + _velocity.x, _boxObj.getPosition().y + _velocity.y);

	/* Keep the alien inside the playarea */
	if (_boxObj.getPosition().x + _boxObj.getSize().x > width) {
		if (_angry != 1) {
		accelerate(sf::Vector2f(-2, _velocity.y), level);
		}
		else {
			accelerate(sf::Vector2f(-2.5, _velocity.y), level);
		}
	}
	if (_boxObj.getPosition().x < 0) {
		if (_angry != 1) {
			accelerate(sf::Vector2f(2, _velocity.y), level);
		}
		else {
			accelerate(sf::Vector2f(2.5, _velocity.y), level);
		}
	}
	if (_boxObj.getPosition().y + _boxObj.getSize().y > height) {
		//The alien goes into a enraged mode with increased speed and shoots more projectiles
		_angry = true;
		setColor(sf::Color::Red);
		setPosition(sf::Vector2f(_boxObj.getPosition().x, 0));
		if (_velocity.x > 0) {
			accelerate(sf::Vector2f(2.5, 0.5));
		}
		else {
			accelerate(sf::Vector2f(-2.5, 0.5));
		}
	}

	/* Alien firing logic */
	if ((LastFire().asMilliseconds() >= 750 & rand() % 100 > 98 )|| (LastFire().asMilliseconds() >= 1500)) {
		ents.push_back(new Bomb(sf::Vector2f(
			_boxObj.getPosition().x + _boxObj.getSize().x / 2,
			_boxObj.getPosition().y + _boxObj.getSize().y + 1)));
		ents[ents.size() - 1]->accelerate(sf::Vector2f(0, 3), level);
		if (_angry == 1) {
			ents.push_back(new Bomb(sf::Vector2f(
				_boxObj.getPosition().x + _boxObj.getSize().x / 2,
				_boxObj.getPosition().y + _boxObj.getSize().y + 1)));

			ents[ents.size() - 1]->accelerate(sf::Vector2f(2, 3), level);

			ents.push_back(new Bomb(sf::Vector2f(
				_boxObj.getPosition().x + _boxObj.getSize().x / 2,
				_boxObj.getPosition().y + _boxObj.getSize().y + 1)));

			ents[ents.size() - 1]->accelerate(sf::Vector2f(-2, 3), level);
		}
		resetLastFire();
	}
}

void Alien::accelerate(sf::Vector2f newVel, int level) {
	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
		if (newVel.x > 0) {
		_velocity.x = newVel.x + (level / 3);
		}
		else {
			_velocity.x = newVel.x - (level / 3);
		}
	}
	_velocity.y = newVel.y;
}

int Alien::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit == true && ent->getType() == 2) {
		ent->setActive(false);
		_active = false;
		return 1; // it's a hit and the updater will have to cover it
	}
	return 0;
}

void Alien::onDestroy(entity::entVec &ents) {
	ents.push_back(new Explosion(sf::Vector2f(
		_boxObj.getPosition().x + _boxObj.getSize().x/2,
		_boxObj.getPosition().y + _boxObj.getSize().y/2
	)));
}

sf::Time Alien::LastFire() {
	_lastFire = _alienClock.getElapsedTime();
	return _lastFire;
}

void Alien::resetLastFire() {
	_lastFire = _alienClock.restart();
}