#include "core.h"
#include <iostream>
#include <SFML/graphics.hpp>
#include <stdlib.h>
#include <chrono>


/* https://en.sfml-dev.org/forums/index.php?topic=5667.0 */
Core::Core(int width, int height) :
	_window(sf::VideoMode(width, height), "Game demo"),
	_mC(), _bombs(),_deadBombs(), _lazers(), _deadLazers(), _swarm(), _deadSwarm(),_lose(false), _win(false),
	_width(width), _height(height),_score(0),_level(1) {
	
	/*
	TODO/NOTES
	Alla ställen där [i]->getRect()->getSize().x/y kallas går att ändra till en temp vector2f
	för att minska antalet funktions calls. minnet bör gå upp lite men borde bli mindre processing eftersom
	man bara kallar getRect()->getSize() en gång.
	*/

	std::srand((unsigned int)std::chrono::high_resolution_clock::now().time_since_epoch().count());

	_swarm.push_back(new Alien());
	_swarm.at(0)->accelerate(sf::Vector2f(2, 0.5), _level);
	_mC = player();
	loop();
}

void Core::render(int lastRender) { //Variabeln är till för interpolation om ja hinner med det
	//std::cout << "render" << std::endl;
	_window.clear();
	_window.draw(*_mC.getRect());

	/* Note: on render a size variable is used to optimise 
		but for update it isn't. Reason is that in update for loops
		arrays are tampered with, elements are added and removed inside
		the loops. Thus a static size creates out of bounds issues and elements
		not getting updated.
	*/

	size_t swarmSize = _swarm.size();
	for (int i = 0; i < swarmSize; i++) {
		_window.draw(*_swarm[i]->getRect());
	}

	size_t bombSize = _bombs.size();
	for (int i = 0; i < bombSize; i++) {
		_window.draw(*_bombs[i]->getRect());
	}

	size_t lazerSize = _lazers.size();
	for (int i = 0; i < lazerSize; i++) {
		_window.draw(*_lazers[i]->getRect());
	}

	_window.display();
}

//TODO bryt ut de olika logiska delarna till egna funktioner, update blir väldigt stor annars.
void Core::update() {
	// gör så rutan går att stänga men ska det vara en while loop verkligen? och om window closar så måste
	// vi stänga av loopen etc och stänga av programmet till main.
	sf::Event evnt;
	while (_window.pollEvent(evnt)) {

		if (evnt.type == sf::Event::Closed) {
			_window.close();
		}
	}

/* MC logic */
	controller();
	_mC.move();
/* To avoid the player not stopping, aka pacman movement */
	_mC.accelerate(sf::Vector2f(0, 0));

/* Keeping mc(main character) within the bounds of the play area. */
	if (_mC.getPosition().x > _width) {
		_mC.setPosition(sf::Vector2f(0, _mC.getPosition().y));
	}
	if (_mC.getPosition().x + _mC.getRect()->getSize().x < 0) {
		_mC.setPosition(sf::Vector2f((float)_width, (float)_mC.getPosition().y));
	}

	if (_mC.getPosition().y < 0) {
		_mC.setPosition(sf::Vector2f(_mC.getPosition().x, 0));
	}

	if (_mC.getPosition().y > (_height - _mC.getRect()->getSize().y)) {
		std::cout << "hit" << std::endl;
		_mC.setPosition(sf::Vector2f(_mC.getPosition().x, _height - _mC.getRect()->getSize().y));
	}

/*	spawn logic */
	if (std::rand() % 120 == 1) {

		if (_deadSwarm.size() > 0) {
			_deadSwarm[0]->setActive(true);
			_swarm.push_back(_deadSwarm[0]);
			_deadSwarm.erase(_deadSwarm.begin());

			_swarm[_swarm.size() - 1]->setPosition(sf::Vector2f(rand() % _width, 0));
			_swarm[_swarm.size() - 1]->accelerate(sf::Vector2f(2, 0.5), _level);
		}
		else {
			_swarm.push_back(new Alien(sf::Vector2f(std::rand() % _width, 0), sf::Vector2f(20, 20)));
		
			float tempSpeed = 1;
			if (std::rand() % 2 == 0) {
				tempSpeed = 2;
			}
			else{
				tempSpeed = -2;
			}
			_swarm.back()->accelerate(sf::Vector2f(tempSpeed,0.5),_level);
		}
	}

/* Alien logic*/
	for (int i = 0; i < _swarm.size(); i++) {
		_swarm[i]->move();
	/* Alien movement logic */

		/* Keep the aliens inside the playarea */
		if (_swarm[i]->getPosition().x + _swarm[i]->getRect()->getSize().x > _width) {
			_swarm[i]->accelerate(sf::Vector2f(-2, _swarm[i]->getVelocity().y), _level);
		}
		if (_swarm[i]->getPosition().x < 0) {
			_swarm[i]->accelerate(sf::Vector2f(2, _swarm[i]->getVelocity().y),_level);
		}
		if (_swarm[i]->getPosition().y + _swarm[i]->getRect()->getSize().y > _height) {
			//lose a life and alien goes inactive/dissapears.
			_swarm[i]->accelerate(sf::Vector2f(0, 0), _level);
			_swarm[i]->setActive(false);
			_deadSwarm.push_back(_swarm[i]);
			_swarm.erase(_swarm.begin() + i);
		}

	/* Alien firing logic */
		if (rand() % 100 == 1) {
			if (_deadBombs.size() > 0 ){
				_bombs.push_back(_deadBombs[0]);
				_deadBombs.erase(_deadBombs.begin());

				_bombs[_bombs.size() - 1]->setPosition(sf::Vector2f(
					_swarm[i]->getPosition().x + _swarm[i]->getRect()->getSize().x / 2,
					_swarm[i]->getPosition().y + _swarm[i]->getRect()->getSize().y + 1));
				
				_bombs[_bombs.size() - 1]->accelerate(sf::Vector2f(0, 3), _level);
			}
			else{
				_bombs.push_back(new Bomb(sf::Vector2f(
					_swarm[i]->getPosition().x + _swarm[i]->getRect()->getSize().x/2,
					_swarm[i]->getPosition().y + _swarm[i]->getRect()->getSize().y + 1)));

				_bombs[_bombs.size() - 1]->accelerate(sf::Vector2f(0, 3), _level);
			}
		}
	}

/* Bomb logic */
	for (int i = 0; i < _bombs.size(); i++) {
		_bombs[i]->move();
	/* Bomb movement logic */
		if (_bombs[i]->getPosition().x + _bombs[i]->getRect()->getSize().x > _width) {
			_bombs[i]->setPosition(sf::Vector2f(
				_width - _bombs[i]->getRect()->getSize().x, _bombs[i]->getRect()->getSize().y
				));
		}

		if (_bombs[i]->getPosition().x < 0) {
			_bombs[i]->setPosition(sf::Vector2f(
				0, _bombs[i]->getRect()->getSize().y
				));
		}

		if (_bombs[i]->getPosition().y + _bombs[i]->getRect()->getSize().y > _height) {
			std::cout << " direkt " << std::endl;
			_bombs[i]->accelerate(sf::Vector2f(0, 0), _level);
			std::cout << "flyttar bomb " << std::endl;
			_deadBombs.push_back(_bombs[i]);
			std::cout << " tar bort gammal bomb" << std::endl;
			_bombs.erase(_bombs.begin() + i);
			std::cout << " klar" << std::endl;
		}
	}

/* Lazer logic */

/* Collision logic */
}

void Core::controller() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
	//	std::cout << "left klicked" << std::endl;
		_mC.accelerate(sf::Vector2f(-2, _mC.getVelocity().y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
		//std::cout << "righ klicked" << std::endl;
		_mC.accelerate(sf::Vector2f(2, _mC.getVelocity().y));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
	//	std::cout << "down klicked" << std::endl;
		_mC.accelerate(sf::Vector2f(_mC.getVelocity().x, 2));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
	//	std::cout << "up klicked" << std::endl;
		_mC.accelerate(sf::Vector2f(_mC.getVelocity().x, -2));
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		std::cout << " space clicked:  ";
		if (_mC.LastFire().asMilliseconds() >= 1000) {
			//TODO fire event stuff.
			std::cout << "fire!!!" << std::endl;
			_mC.resetLastFire();
		}
		std::cout << " blank______" << std::endl;
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

	// To monitor fps
	int counter = 0;

	while (gameRunning) {
		current = clock.getElapsedTime();
		lastUpdateT = UpdateClock.getElapsedTime();
		lastRenderT = RenderClock.getElapsedTime();

		// Calling update 
		if (lastUpdateT.asMicroseconds() > 16100) { 
			update();
			lastUpdateT = UpdateClock.restart();
		}

		// FPS counter
		if (current.asMilliseconds() > 1000) {
			_frames = counter;
			std::cout << "frames: " << _frames << std::endl;
			std::cout << "dead size: " << _deadSwarm.size() << " swarm size: " << _swarm.size() 
				<< " total: " << _deadSwarm.size()+_swarm.size() << std::endl;
			std::cout << "dead size: " << _deadBombs.size() << " bomb size: " << _bombs.size() << 
				" total: " << _deadBombs.size() + _bombs.size() << std::endl;
			counter = 0;
			current = clock.restart();
		}

		// Calling render 
		if (lastRenderT.asMicroseconds() > 16100) {
			render(lastRenderT.asMilliseconds());
			lastRenderT = RenderClock.restart();
			counter++;
		}
	}
}

