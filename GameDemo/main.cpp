#include <SFML/Graphics.hpp>
#include "core.h"
#include <iostream>

using namespace std;

int main() {
	//sf::RenderWindow window(sf::VideoMode(640, 480), "Game demo");
	cout << "starting" << endl;
	Core(640, 480);

	return 0;

	/*while (window.isOpen()) {

		sf::Event evnt;
		while (window.pollEvent(evnt)) {

			if (evnt.type == sf::Event::Closed) {
				window.close();
			}

			window.clear();
			window.draw(circle);
			window.display();
		}
	}*/
}