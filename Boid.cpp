#define _USE_MATH_DEFINES
#include "Boid.hpp"
#include <math.h>
#include "functions.hpp"


Boid::Boid(Vector2f pos, Vector2f vel, float size, Color color) 
	: shape(3), velocity(vel)
{
	shape.setPoint(0, Vector2f(-size * 3 / 8, -size / 2));
	shape.setPoint(1, Vector2f(size * 3 / 8, -size / 2));
	shape.setPoint(2, Vector2f(0.f, size / 2));
	shape.setFillColor(color);
	shape.setPosition(pos);
}

void Boid::draw(RenderWindow& window) {
	window.draw(shape);
}

void Boid::update(Time dt) {
	// move
	shape.move(velocity * dt.asSeconds());

	// turn towards velocity
	double angle = atan(-velocity.x / velocity.y);
	if (velocity.y < 0) {
		angle = M_PI + angle;
	}
	shape.setRotation(degrees(angle));
}


