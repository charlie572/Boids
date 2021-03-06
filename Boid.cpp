#define _USE_MATH_DEFINES
#include "Boid.hpp"
#include <math.h>
#include "functions.hpp"

float Boid::WALL_AVOIDANCE = 750.f;
float Boid::BOID_AVOIDANCE = 4000.f;
float Boid::VISION_RADIUS = 150.f;
float Boid::VELOCITY_MATCHING = 5.f;
float Boid::FLOCK_CENTERING = 5.f;
float Boid::FOV = M_PI * 0.75;
float Boid::MAX_SPEED = 300.f;
float Boid::MAX_SPEED_SQUARED = square(Boid::MAX_SPEED);

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
	shape.move(velocity * dt.asSeconds() + 0.5f * acceleration * square(dt.asSeconds()));

	// update velocity
	velocity += acceleration * dt.asSeconds();

	// limit speed
	float magnitude_squared = get_magnitude_squared(velocity);
	if (magnitude_squared > MAX_SPEED_SQUARED) {
		float magnitude = sqrt(magnitude_squared);
		velocity.x *= MAX_SPEED / magnitude;
		velocity.y *= MAX_SPEED / magnitude;
	}

	// turn towards velocity
	shape.setRotation(degrees(get_angle(velocity)));
}

void Boid::avoid_walls(float width, float height) {
	float x = get_position().x;
	float y = get_position().y;

	if (x <= VISION_RADIUS) {
		acceleration.x += WALL_AVOIDANCE / x;
	}
	else if (x >= width - VISION_RADIUS) {
		acceleration.x -= WALL_AVOIDANCE / (width - x);
	}

	if (y <= VISION_RADIUS) {
		acceleration.y += WALL_AVOIDANCE / x;
	}
	else if (y >= height - VISION_RADIUS) {
		acceleration.y -= WALL_AVOIDANCE / (height - y);
	}
}

void Boid::interact(vector<Boid>& neighbours) {
	if (neighbours.size() > 0) {
		Vector2f total_vel;
		Vector2f mean_pos;
		for (int i = 0; i < neighbours.size(); i++) {
			// collision avoidance
			Vector2f heading = neighbours[i].get_position() - get_position();
			acceleration -= heading * (BOID_AVOIDANCE / get_magnitude_squared(heading));

			// total velocity and position
			mean_pos += neighbours[i].get_position();
			total_vel += neighbours[i].get_velocity();
		}

		// calculate mean velocity
		mean_pos *= 1.f / neighbours.size();

		// velocity matching
		acceleration += normalise(total_vel - velocity) * VELOCITY_MATCHING;

		// flock centering
		acceleration += (mean_pos - get_position()) * FLOCK_CENTERING;
	}
}

void Boid::wrap(float width, float height) {
	if (get_position().x < 0) shape.move(width, 0.f);
	else if (get_position().x > width) shape.move(-width, 0.f);

	if (get_position().y < 0) shape.move(0.f, height);
	else if (get_position().y > height) shape.move(0.f, -height);
}

bool Boid::in_view(Boid& boid) {
	float angle = get_angle(boid.get_position() - get_position()) - get_angle(velocity);
	while (angle < 0) angle *= -1;
	while (angle > M_PI) angle -= M_PI;

	if (angle <= FOV / 2) {
		float distance_squared = get_magnitude_squared(boid.get_position() - get_position());
		return distance_squared < square(Boid::VISION_RADIUS);
	}

	return false;
}
