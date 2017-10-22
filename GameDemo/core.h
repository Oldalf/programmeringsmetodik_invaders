#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "entity.h"

class Core {
public:
	Core(int width = 640, int height = 480);
	void render(int lastRender);	// Add args that are needed for render
	void update(sf::Clock &spawntimer); // Add ars that are needed for updating the game, logic and such..
	void loop(); // Add args needed, contains the while loop that runs the window and sends update and render calls.

private:
	void collision();
	void cleaner();
	void spawner(sf::Clock &spawnClock);
	int _width, _height;
	bool gameRunning = true;
	sf::RenderWindow _window;
	bool _lose;
	entity::entVec _entities;
	player _mC;
	int _level, _score,_frames, _life;
	sf::Text _scoreT;
	sf::Text _lifeT;
};