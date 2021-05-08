#include "SFML\Graphics.hpp"
#include "Game.hpp"

using namespace std;
using namespace sf;


int main() {
	RenderWindow window(VideoMode(600, 600), "boids");
	Game game(600.f, 600.f);

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
