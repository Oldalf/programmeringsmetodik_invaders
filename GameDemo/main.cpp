#include <SFML/Graphics.hpp>
#include "core.h"
#include <iostream>

using namespace std;

int main() {
	//sf::RenderWindow window(sf::VideoMode(640, 480), "Game demo");
	cout << "starting" << endl;
	Core(640, 480);

	system("pause");
	return 0;
}