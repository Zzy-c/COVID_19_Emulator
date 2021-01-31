#include "Random.h"

int Random::Range(int a, int b) {
	return a + rand() % (b - a + 1);
}

bool Random::Percent(int value) {
	if (Range(1, 100) <= value)return true;
	return false;
}