#ifndef BOID_H
#define BOID_H

#include "SFML\Graphics.hpp"

using namespace sf;

class Boid
{
private:
	ConvexShape shape;
	Vector2f velocity;

public:
	Boid(Vector2f pos, Vector2f vel, float size, Color color = Color::White);
	void draw(RenderWindow& window);
	void update(Time dt);
	inline
		Vector2f get_position() { return shape.getPosition(); }
	inline
		Vector2f get_velocity() { return velocity; }
};

#endif

