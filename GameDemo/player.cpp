#include "entity.h"

player::player(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	entity(position, size, color, maxVelX), _playerClock(),_lastFire(_playerClock.getElapsedTime()) {
	_type = 0;
	_damage = 1;
	_renderPrio = 0;
}

void player::update(entity::entVec &ents, int width, int height, int level) {

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		accelerate(sf::Vector2f(-2, _velocity.y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) || sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		accelerate(sf::Vector2f(2, _velocity.y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down) || sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		accelerate(sf::Vector2f(_velocity.x, 2));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) || sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		accelerate(sf::Vector2f(_velocity.x, -2));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		if (LastFire().asMilliseconds() >= 500) {
			sf::Vector2f tempPos = _boxObj.getPosition();
			sf::Vector2f tempSize = _boxObj.getSize();

			ents.push_back(new Lazer(sf::Vector2f(
					tempPos.x + tempSize.x / 2,
					tempPos.y - 5)));
			ents[ents.size() - 1]->accelerate(sf::Vector2f(0, -3));

				ents.push_back(new Lazer(sf::Vector2f(
					tempPos.x + tempSize.x / 2,
					tempPos.y - 5)));
				ents[ents.size() - 1]->accelerate(sf::Vector2f(2, -3));

				ents.push_back(new Lazer(sf::Vector2f(
					tempPos.x + tempSize.x / 2,
					tempPos.y - 5)));
				ents[ents.size() - 1]->accelerate(sf::Vector2f(-2, -3));
			resetLastFire();
		}
	}

	_boxObj.setPosition(_boxObj.getPosition().x + _velocity.x, _boxObj.getPosition().y + _velocity.y);

	//För att slippa pacman movement.
	accelerate(sf::Vector2f(0, 0));

	if (_boxObj.getPosition().x + _boxObj.getSize().x > width) {
		_boxObj.setPosition(sf::Vector2f(width - _boxObj.getSize().x, _boxObj.getPosition().y));
	}
	if (_boxObj.getPosition().x < 0) {
		_boxObj.setPosition(sf::Vector2f(0, _boxObj.getPosition().y));
	}
	if (_boxObj.getPosition().y < 0) {
		_boxObj.setPosition(sf::Vector2f(_boxObj.getPosition().x, 0));
	}
	if (_boxObj.getPosition().y > (height - _boxObj.getSize().y)) {
		_boxObj.setPosition(sf::Vector2f(_boxObj.getPosition().x, height - _boxObj.getSize().y));
	}
}

void player::accelerate(sf::Vector2f newVel, int level) {
	if (newVel.x <= _maxVelX || newVel.x >= -_maxVelX) {
		_velocity.x = newVel.x;
	}
	_velocity.y = newVel.y;
}

int player::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit && (ent->getType() == 1 || ent->getType() == 3)) {
		return 1;
	}
	else {
		return 0;
	}
}

sf::Time player::LastFire(){
	_lastFire = _playerClock.getElapsedTime();
	return _lastFire;
}

void player::resetLastFire() {
	_lastFire = _playerClock.restart();
}