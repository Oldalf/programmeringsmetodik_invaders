#pragma once
#include "entity.h"

class player : public entity {
public:
	player(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(20, 20),
		sf::Color color = sf::Color::Magenta, float maxVelX = 1.0f);

	int getLife() const;
	int collide(entity *ent);
	sf::Time LastFire();
	void resetLastFire();
	void setLife(int newLife = 2);

private:
	int subtractLife();
	int _life;
	sf::Time _lastFire;
	sf::Clock _playerClock;
};