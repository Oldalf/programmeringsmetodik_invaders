#pragma once

#include "SFML/graphics.hpp"

class entity {
public:
	entity(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(10,10), 
		sf::Color color = sf::Color::Green, float maxVelX = 1.0f);
	void move();
	virtual void accelerate(sf::Vector2f newVel);
	bool collision(entity *ent); //FIXME fixa med pekare/referens plus byt ut mot en collide grej abstract.
	virtual int collide(entity *ent) = 0;
	sf::Vector2f getPosition() const;
	int getType() const;
	sf::RectangleShape* getRect(); //FIXME returnera en pekare/referens.
	sf::Vector2f getVelocity() const;
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);
	virtual ~entity();
protected:
	
	sf::RectangleShape _boxObj;
	sf::Vector2f _velocity;
	float _maxVelX;
	int _type; // 0 = player, 1 = alien, 2 = lazer(playershot) 3 = bomb(alien shot)
};

class Lazer : public entity {
public:
	Lazer(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f size = sf::Vector2f(2,5),
		sf::Color color = sf::Color::White, float maxVelX = 0);
	int collide(entity *ent);
};

class Bomb : public entity {
public:
	Bomb(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(5, 4),
		sf::Color color = sf::Color::Yellow, float maxVelX = 0);
	int collide(entity *ent);
	void accelerate(sf::Vector2f newVel = sf::Vector2f(0,3));
	void accelerate(sf::Vector2f newVel = sf::Vector2f(0,3), int level = 1);
};