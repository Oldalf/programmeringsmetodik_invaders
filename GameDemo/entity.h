#pragma once

#include "SFML/graphics.hpp"
#include <vector>

//TODO fixa texturer, inget fancy bara något enkelt.
class entity {
public:
	typedef std::vector<entity*> entVec;
	entity(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(10,10), 
		sf::Color color = sf::Color::Green, float maxVelX = 1.0f);
	virtual ~entity();
	virtual void update(entVec &ents, int width, int height, int level = 1) = 0;
	virtual void accelerate(sf::Vector2f newVel, int level = 1) = 0; 
	virtual int collide(entity *ent) = 0;
	virtual void onDestroy(entVec &ent);
	sf::Vector2f getPosition() const;
	int getType() const;
	int getDamage() const;
	int getRenderPrio() const;
	bool active() const;
	sf::RectangleShape* getRect();
	sf::Vector2f getVelocity() const;
	void setActive(bool newACt);
	void setSize(sf::Vector2f size);
	void setPosition(sf::Vector2f position);
	void setColor(sf::Color color);
	void setRenderPrio(int prio);
protected:
	bool collision(entity *ent);
	sf::RectangleShape _boxObj;
	sf::Vector2f _velocity;
	float _maxVelX;
	int _type; // 0 = player, 1 = alien, 2 = lazer(playershot), 3 = bomb(alien shot),  4 = explosion
	int _damage, _renderPrio;
	bool _active;
};

class player : public entity {
public:
	player(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(20, 20),
		sf::Color color = sf::Color::Magenta, float maxVelX = 1.0f);
	void update(entVec &ents,int width, int height, int level = 1);
	void accelerate(sf::Vector2f newVel, int level = 1);
	int collide(entity *ent);
private:
	void resetLastFire();
	sf::Time LastFire();
	sf::Time _lastFire;
	sf::Clock _playerClock;
};

class Alien : public entity {
public:
	Alien(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(20, 20),
		sf::Color color = sf::Color::Green, float maxVelX = 1.0f);
	void update(entVec &ents, int width, int height, int level = 1);
	void accelerate(sf::Vector2f newVel, int level = 1);
	int collide(entity *ent);
	void onDestroy(entVec &ent);
private:
	void resetLastFire();
	bool _angry;
	sf::Time LastFire();
	sf::Time _lastFire;
	sf::Clock _alienClock;
};

class Lazer : public entity {
public:
	Lazer(sf::Vector2f position = sf::Vector2f(0,0), sf::Vector2f size = sf::Vector2f(2,5),
		sf::Color color = sf::Color::White, float maxVelX = 0);
	void update(entVec &ents, int width, int height, int level = 1);
	void accelerate(sf::Vector2f newVel, int level = 1);
	int collide(entity *ent);
private:
};

class Bomb : public entity {
public:
	Bomb(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(5, 4),
		sf::Color color = sf::Color::Yellow, float maxVelX = 0);
	void update(entVec &ents, int width, int height, int level = 1);
	void accelerate(sf::Vector2f newVel, int level = 1);
	int collide(entity *ent);
};

class Explosion : public entity {
public:
	Explosion(sf::Vector2f position = sf::Vector2f(0, 0), sf::Vector2f size = sf::Vector2f(15, 15),
		sf::Color color = sf::Color::Cyan, float maxVelX = 0);
	void update(entVec &ents, int width, int height, int level = 1);
	void accelerate(sf::Vector2f newVel, int level = 1);
	int collide(entity *ent);
	void onDestroy(entVec &ent);
private:
	int _lifeTime;
};