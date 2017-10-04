#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "player.h"
#include "Alien.h"

class Core {
public:
	Core(int width = 640, int height = 480);
	void render(int lastRender);	// Add args that are needed for render
	void update(); // Add ars that are needed for updating the game, logic and such.
	void controller(); //  Supposed to control the logic and flow of the game. probably not void.
	void loop(); // Add args needed, contains the while loop that runs the window and sends update and render calls.

private:
	int _width, _height;
	bool gameRunning = true;
	sf::RenderWindow _window;
	bool _win, _lose;
	typedef std::vector<entity*> EntityVector;
	std::vector<Alien*> _swarm;
	player _mC;
	int level, score;
};