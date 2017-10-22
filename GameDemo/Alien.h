#pragma once
#include "entity.h"

class Alien : public entity {
public:
	Alien(sf::Vector2f position = sf::Vector2f(10, 0), sf::Vector2f size = sf::Vector2f(20, 20),
		sf::Color color = sf::Color::Red, float maxVelX = 6.0f);
	int collide(entity *ent);
	void accelerate(sf::Vector2f newVel = sf::Vector2f(2, 0.5), int level = 1);
private:
};