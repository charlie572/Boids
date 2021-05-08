#include "Boid.hpp"


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
	shape.move(velocity * dt.asSeconds());
}


