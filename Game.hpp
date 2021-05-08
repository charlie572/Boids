#ifndef GAME_H
#define GAME_H

#include "SFML\Graphics.hpp"
#include "Boid.hpp"
#include <vector>

using namespace sf;
using namespace std;

class Game
{
private:
	const float WIDTH;
	const float HEIGHT;
	vector<Boid> boids;

public:
	Game(float width, float height, int num_boids);
	void draw(RenderWindow& window);
	void update(Time dt);
};

#endif

