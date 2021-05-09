#include "SFML\Graphics.hpp"
#include "Game.hpp"
#include "functions.hpp"
#include <iostream>

using namespace std;
using namespace sf;


int main() {
	srand(time(0));

	RenderWindow window(VideoMode(960, 960), "boids");
	Game game(960.f, 960.f, 100);

	Event event;
	Time dt;
	Clock clock;
	while (window.isOpen()) {
		dt = clock.restart();

		while (window.pollEvent(event)) {
			if (event.type == Event::Closed) window.close();
		}

		game.update(dt);

		window.clear();
		game.draw(window);
		window.display();
	}
}
