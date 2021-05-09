#include "Game.hpp"
#include "functions.hpp"

Game::Game(float width, float height, int num_boids)
	: WIDTH(width), HEIGHT(height) 
{
	Vector2f position;
	Vector2f velocity;

	for (int i = 0; i < num_boids; i++) {
		position.x = random_float(0.f, width);
		position.y = random_float(0.f, height);
		velocity.x = random_float(-500.f, 500.f);
		velocity.y = random_float(-500.f, 500.f);
		boids.push_back(Boid(position, velocity, 10.f));
	}
}

void Game::draw(RenderWindow& window) {
	for (int i = 0; i < boids.size(); i++) {
		boids[i].draw(window);
	}
}

void Game::update(Time dt) {
	for (int i = 0; i < boids.size() - 1; i++) {
		boids[i].reset_acceleration();

		vector<Boid> neighbours;
		for (int j = 0; j < boids.size(); j++) {
			if (j != i) {
				if (boids[i].in_view(boids[j])) {
					neighbours.push_back(boids[j]);
				}
			}

			boids[i].interact(neighbours);
			neighbours.clear();
		}
	}

	for (int i = 0; i < boids.size(); i++) {
		// boids[i].avoid_walls(WIDTH, HEIGHT);
		boids[i].update(dt);
		boids[i].wrap(WIDTH, HEIGHT);
	}
}
