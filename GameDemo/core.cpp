#include "core.h"
#include <iostream>
#include <SFML/graphics.hpp>

/* https://en.sfml-dev.org/forums/index.php?topic=5667.0 */
Core::Core(int width, int height) :
_window(sf::VideoMode(width, height), "Game demo"){
	loop();
}

void Core::render(int lastRender) {
	//std::cout << "render" << std::endl;
	_window.clear();
	sf::CircleShape shape(100.f);
	shape.setFillColor(sf::Color::Green);
	_window.draw(shape);
	_window.display();
}

void Core::update() {
	/*std::cout << "update" << std::endl;*/
	
	//FIXME vet inte om det ska vara enw hile loop här.
	sf::Event evnt;
	while (_window.pollEvent(evnt)) {

		if (evnt.type == sf::Event::Closed) {
			_window.close();
		}
	}
}

void Core::controller() {

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
