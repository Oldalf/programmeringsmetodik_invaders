#include "core.h"
#include <iostream>
#include <SFML/graphics.hpp>

/* https://en.sfml-dev.org/forums/index.php?topic=5667.0 */
Core::Core(int width, int height) :
	_window(sf::VideoMode(width, height), "Game demo"),
	_mC(), _swarm(), _lose(false), _win(false),
	_width(width), _height(height),_score(0),_level(1) {

	_swarm.push_back(new Alien());
	_swarm.push_back(new Alien(sf::Vector2f(50,20),sf::Vector2f(10,10)));
	_mC = player();
	loop();
}

void Core::render(int lastRender) { //Variabeln är till för interpolation om ja hinner med det
	//std::cout << "render" << std::endl;
	_window.clear();
	_window.draw(*_mC.getRect());
	for (int i = 0; i < _swarm.size(); i++) {
		_window.draw(*_swarm[i]->getRect());
	}
	_window.display();
}

void Core::update() {
	/*std::cout << "update" << std::endl;*/
	
	//FIXME vet inte om det ska vara en while loop här.
	sf::Event evnt;
	while (_window.pollEvent(evnt)) {

		if (evnt.type == sf::Event::Closed) {
			_window.close();
		}
	}

	/* MC logic */
	controller();
	_mC.move();
		/* Keeping mc within the bounds of the play area. */
	if (_mC.getPosition().x > _width) {
		_mC.setPosition(sf::Vector2f(0, _mC.getPosition().y));
	}
	if (_mC.getPosition().x < 0) {
		_mC.setPosition(sf::Vector2f(_width, _mC.getPosition().y));
	}

	if (_mC.getPosition().y < 0) {
		_mC.setPosition(sf::Vector2f(_mC.getPosition().x, 0));
	}

	if (_mC.getPosition().y > (_height - _mC.getRect()->getSize().y)) {
		std::cout << "hit" << std::endl;
		_mC.setPosition(sf::Vector2f(_mC.getPosition().x, _height - _mC.getRect()->getSize().y));
	}

	/* Alien logic */
	for (int i = 0; i < _swarm.size(); i++) {
		_swarm[i]->move();

		/* Keep the aliens inside the playarea */
		if (_swarm[i]->getPosition().x > _width) {
			_swarm[i]->accelerate(sf::Vector2f(-2, _swarm[i]->getVelocity().y), _level);
		}
		if (_swarm[i]->getPosition().x < 0) {
			_swarm[i]->accelerate(sf::Vector2f(2, _swarm[i]->getVelocity().y),_level);
		}
		if (_swarm[i]->getPosition().y > _height) {
			//lose a life and alien goes inactive/dissapears.
		}
	}
}

void Core::controller() {
	//FIXME "ghosting" man kan inte åka snett upp vänster t.ex.
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
	int frames = 0;

	while (gameRunning) {
		current = clock.getElapsedTime();
		lastUpdateT = UpdateClock.getElapsedTime();
		lastRenderT = RenderClock.getElapsedTime();

		// Calling update 
		if (lastUpdateT.asMicroseconds() > 16100) { 
			update();
			UpdateClock.restart();
			lastUpdateT = UpdateClock.getElapsedTime();
		}

		// FPS counter
		if (current.asMilliseconds() > 1000) {
			frames = counter;
			std::cout << "frames: " << frames << std::endl;
			counter = 0;
			clock.restart();
			current = clock.getElapsedTime();
		}

		// Calling render 
		if (lastRenderT.asMicroseconds() > 16100) {
			render(lastRenderT.asMilliseconds());
			RenderClock.restart();
			lastRenderT = RenderClock.getElapsedTime();
			counter++;
		}
	}
}

