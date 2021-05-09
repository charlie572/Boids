#ifndef BOID_H
#define BOID_H

#include "SFML\Graphics.hpp"
#include <vector>

using namespace sf;
using namespace std;

class Boid
{
private:
	ConvexShape shape;
	Vector2f velocity;
	Vector2f acceleration;

public:
	static float WALL_AVOIDANCE;
	static float BOID_AVOIDANCE;
	static float VISION_RADIUS;
	static float VELOCITY_MATCHING;
	static float FLOCK_CENTERING;
	static float FOV;

	Boid(Vector2f pos, Vector2f vel, float size, Color color = Color::White);
	void draw(RenderWindow& window);
	void update(Time dt);
	inline
		Vector2f get_position() { return shape.getPosition(); }
	inline
		Vector2f get_velocity() { return velocity; }
	inline
		void reset_acceleration() {
			acceleration.x = 0.f;
			acceleration.y = 0.f;
		}
	void avoid_walls(float width, float height);
	void interact(vector<Boid>& neighbours);
	void wrap(float width, float height);
	bool in_view(Boid& boid);
};

#endif

