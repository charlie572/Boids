#include <random>

float random_float(float lower_bound, float upper_bound) {
	float result = float(rand()) / rand() * (upper_bound - lower_bound);
	while (result > upper_bound - lower_bound) {
		result -= upper_bound - lower_bound;
	}

	result += lower_bound;

	return result;
}