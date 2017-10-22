#include "core.h"
#include <iostream>
#include <SFML/graphics.hpp>
#include <stdlib.h>
#include <chrono>
#include <string>

Core::Core(int width, int height) :
	_window(sf::VideoMode(width, height), "Game demo"),
	_mC(), _entities(),_lose(false),
	_width(width), _height(height),_score(0),_level(1), _life(100) {
	
	std::srand((unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count());

	_entities.push_back(new Alien(sf::Vector2f(0,0)));
	_entities.at(0)->accelerate(sf::Vector2f(2, 0.5), _level);
	_mC = player(sf::Vector2f(_width/2, _height/2));

	sf::Font font;
	font.loadFromFile("arial.ttf");
	
	_scoreT = sf::Text("Score: ", font, 12);
	_scoreT.setFillColor(sf::Color::White);
	_scoreT.setPosition(_width - 100, 5);
	_scoreT.setStyle(sf::Text::Bold);

	_lifeT = sf::Text("Life ", font, 12);
	_lifeT.setFillColor(sf::Color::White);
	_lifeT.setPosition(2, 5);
	_lifeT.setStyle(sf::Text::Bold);
	
	loop();
}

void Core::render(int lastRender) { //Variabeln är till för interpolation om ja hinner med det
	_window.clear();
	_window.draw(*_mC.getRect());
	entity::entVec tempRend;

	for(entity::entVec::iterator i = _entities.begin(); i != _entities.end(); i++) {
		entity *e = *i;
		if (e->getRenderPrio() == 0) {
			tempRend.push_back(e);
			continue;
		}
		_window.draw(*e->getRect());
	}

	for (entity::entVec::iterator i = tempRend.begin(); i != tempRend.end(); i++) {
		entity *e = *i;
		_window.draw(*e->getRect());
	}

	_window.draw(_scoreT);
	_window.draw(_lifeT);
	_window.display();
}

void Core::update(sf::Clock &spawnClock) {

	if (_life <= 0) {
		_lose = true;
		exit;
	}

	entity::entVec tempEnt(_entities);
	_mC.update(_entities, _width, _height, _level);
	for (entity::entVec::iterator i = tempEnt.begin(); i != tempEnt.end(); i++) {
		entity *e = *i;
		e->update(_entities, _width, _height, _level);
	}

	collision();

	cleaner();
	spawner(spawnClock);
	
	std::string tempLife = "Life: " + std::to_string(_life);
	std::string tempScore = "Score: " + std::to_string(_score);
	_lifeT.setString(tempLife);
	_scoreT.setString(tempScore);
}

void Core::collision() {
	
	entity::entVec tempEnt(_entities);
	/* Collide with player */
	for (entity::entVec::iterator i = tempEnt.begin(); i != tempEnt.end(); i++) {
		entity *e = *i;
		int res = _mC.collide(e);
		if (res == 1) {
			e->setActive(false);
			_life -= e->getDamage();
		}
	}
	
	/* Collide with other elements*/
	for (entity::entVec::iterator i = tempEnt.begin(); i != tempEnt.end(); i++) {
		entity *e1 = *i;
		if (!e1->active()) {
			continue;
		}
		for (entity::entVec::iterator j = i; j != tempEnt.end(); j++) {
			entity *e2 = *j;
			if (!e2->active()) {
				continue;
			}
			e1->collide(e2);
		}
	}
}

void Core::cleaner() {
	entity::entVec tempEnt;
	for (entity::entVec::iterator i = _entities.begin(); i != _entities.end(); i++) {
		entity *e = *i;
		if (e->active()) {
			tempEnt.push_back(e);
		}
		else {
			if (e->getType() == 1) {
				_score += 100;
				if (_score % 2000 == 0) {
					_level++;
				}
			}
			e->onDestroy(tempEnt);
			delete e;
		}
	}
	_entities = tempEnt;
}

void Core::spawner(sf::Clock &spawnClock) {
	sf::Time spawnTimer = spawnClock.getElapsedTime();
	if ((spawnTimer.asMilliseconds() >= 500 & rand() % 100 > 98 )|| (spawnTimer.asMilliseconds() >= 1250)) {

		_entities.push_back(new Alien(sf::Vector2f(std::rand() % _width, 0)));
		
		float tempSpeed = 1;
		if (std::rand() % 2 == 0) {
			tempSpeed = 2;
		}
		else{
			tempSpeed = -2;
		}
		_entities.back()->accelerate(sf::Vector2f(tempSpeed, 0.5), _level);
		spawnClock.restart();
	}

}

void Core::loop() {
	std::cout << "Loop initialized" << std::endl;

	// In order to handle timings of calls.
	sf::Time lastUpdateT;
	sf::Time lastRenderT;
	sf::Time current;

	sf::Clock clock;
	sf::Clock UpdateClock;
	sf::Clock RenderClock;
	sf::Clock spawnClock;

	// To monitor fps
	int counter = 0;
	sf::Event evnt;
	_window.pollEvent(evnt);

	while (gameRunning && evnt.type != sf::Event::Closed && !_lose) {
		current = clock.getElapsedTime();
		lastUpdateT = UpdateClock.getElapsedTime();
		lastRenderT = RenderClock.getElapsedTime();

		// Calling update 
		if (lastUpdateT.asMicroseconds() > 16000) { 
			update(spawnClock);
			lastUpdateT = UpdateClock.restart();
		} 

		// FPS counter
		if (current.asMilliseconds() > 1000) {
			_frames = counter;
			std::cout << "frames: " << _frames << std::endl;
			std::cout << "Amount of entities: " << _entities.size()+1 << std::endl;
			counter = 0;
			current = clock.restart();
		}

		// Calling render 
		if (lastRenderT.asMicroseconds() > 16000) {
			render(lastRenderT.asMilliseconds());
			lastRenderT = RenderClock.restart();
			counter++;
		}
	_window.pollEvent(evnt);
	}
	_window.close();	
	std::cout << "***********************************" << std::endl;
	std::cout << "\t Game over! \t" << std::endl;
	std::cout << "\t Your score: " << _score << std::endl;
	std::cout << "***********************************\n" << std::endl;
}