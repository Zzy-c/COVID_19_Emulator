#pragma once

#include <cmath>

class vector {
public:
	float x;
	float y;
	vector(float x, float y);
	static float Distance(vector a, vector b);
};