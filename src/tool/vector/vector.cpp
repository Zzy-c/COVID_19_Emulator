#include "vector.h"

vector::vector(float x, float y) {
	this->x = x;
	this->y = y;
}

float vector::Distance(vector a, vector b) {
	return sqrt((a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y));
}