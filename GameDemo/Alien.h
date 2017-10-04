#pragma once
#include "entity.h"

class Alien : public entity {
public:
	Alien(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(10, 10),
		sf::Color color = sf::Color::Red, float maxVelX = 4.0f);

	int collide(entity *ent);
	void accelerate(sf::Vector2f newVel);
	void accelerate(sf::Vector2f newVel, int level);
	bool active() const;
	void setActive(bool b);
private:
	float _fireRate;
	bool _active;
};