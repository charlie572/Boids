#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"

using namespace sf;

class Game
{
private:
	const float WIDTH;
	const float HEIGHT;

public:
	Game(float width, float height);
	void draw(RenderWindow& window);
	void update(Time dt);
};

#endif

