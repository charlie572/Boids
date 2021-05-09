#define _USE_MATH_DEFINES
#include <random>
#include "SFML\Graphics.hpp"

using namespace sf;

float random_float(float lower_bound, float upper_bound) {
	float result = float(rand()) / rand() * (upper_bound - lower_bound);
	while (result > upper_bound - lower_bound) {
		result -= upper_bound - lower_bound;
	}

	result += lower_bound;

	return result;
}

double degrees(double radians) {
	return radians * 180 / M_PI;
}

float square(float x) {
	return x * x;
}

float get_magnitude_squared(Vector2f vec) {
	return square(vec.x) + square(vec.y);
}

float get_angle(Vector2f vec) {
	double angle = atan(-vec.x / vec.y);
	if (vec.y < 0) {
		angle = M_PI + angle;
	}
	return angle;
}
