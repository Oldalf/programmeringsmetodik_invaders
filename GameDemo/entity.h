#pragma once

#include "SFML/graphics.hpp"

class entity {
public:
	entity(sf::Vector2f position = sf::Vector2f(10, 10), sf::Vector2f size = sf::Vector2f(10,10), 
		sf::Color color = sf::Color::Green, float maxVelX = 1.0f);
	void move();
	virtual void accelerate(int x,int y); // skicka in ändringen plus eventuellt level
	virtual bool collision(entity ent);
	// void destroy(); // ska ta bort objektet på något smidigt sätt. typ kalla destruktorn på det.
	int getPositionX() const;
	int getPositionY() const;
	sf::RectangleShape getRect() const;
	void setSize(sf::Vector2f size);
	void setColor(sf::Color color);
protected:
	sf::RectangleShape _boxObj;

	/* Corners for collission detection */
	/*float _bot, _left, _right, _top;*/

	/* Velocity for movements */
	float _velocityX , _velocityY, _maxVelX;
};

class player : public entity {
public:

	bool collision(entity ent);
private:
	void subtractLife();
	int life;
};