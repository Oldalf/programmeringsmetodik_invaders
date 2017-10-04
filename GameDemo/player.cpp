#include "player.h"

/*
*************************************************
********************  Player ********************
*************************************************
*/

player::player(sf::Vector2f position, sf::Vector2f size, sf::Color color, float maxVelX) :
	entity(position, size, color, maxVelX), _playerClock(),_lastFire(_playerClock.getElapsedTime()) {
	_type = 0;
}

int player::collide(entity *ent) {
	bool hit = collision(ent);
	if (hit == true && (ent->getType() == 3 || ent->getType() == 1)) {
		subtractLife();
		return 1;
	}
	else {
		return 0;
	}
}

int player::getLife() const {
	return _life;
}

sf::Time player::LastFire(){
	_lastFire = _playerClock.getElapsedTime();
	return _lastFire;
}

void player::resetLastFire() {
	_lastFire = _playerClock.restart();
}

void player::setLife(int newLife) {
	_life = newLife;
}

int player::subtractLife() {
	_life--;
	return _life;
}
