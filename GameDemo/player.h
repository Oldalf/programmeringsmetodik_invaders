#pragma once
#include "entity.h"

class player : public entity {
public:
	player(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(20, 20),
		sf::Color color = sf::Color::Magenta, float maxVelX = 1.0f);
	void update(entVec &ents, entVec &deadEnts, int level = 1);
	void accelerate(sf::Vector2f newVel, int level = 1);
	bool collision(entity *ent);
	int collide(entity *ent);
	sf::Vector2f getPosition() const;
	int getType();
	bool active() const;
	sf::RectangleShape* getRect();
	sf::Vector2f getVelocity() const;
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);
private:
	void resetLastFire();
	void update(entity::entVec & ent);
	sf::Time LastFire();
	sf::Time _lastFire;
	sf::Clock _playerClock;
};