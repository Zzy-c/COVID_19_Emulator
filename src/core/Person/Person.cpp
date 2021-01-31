#include"Person.h"

#include "data.h"

Person::Person(vector initialPos, State initialState) :pos(initialPos), state(initialState)
{
	trans = glm::mat4(1.0f);
	direction = glm::vec3(Random::Range(-10, 10) / 1000.0, Random::Range(-10, 10) / 1000.0, 0.0f);
	lastCollider = -1;
	incubationTime = incubationReferenceTime + Random::Range(-incubationTimeOffset, incubationTimeOffset);
	worseTime = worseReferenceTime + Random::Range(-worseTimeOffset, worseTimeOffset);
	deathTime = deathReferenceTime + Random::Range(-deathTimeOffset, deathTimeOffset);
	cureTime = cureReferenceTime + Random::Range(-cureTimeOffset, cureTimeOffset);
}

void Person::BeConfirmed() {
	incubationTime -= deltaTime;
	if (incubationTime < 0) {
		state = Person::CONFIRMED;
		incubationTime = incubationReferenceTime + Random::Range(-incubationTimeOffset, incubationTimeOffset);
	}
}
void Person::BeSerious() {
	worseTime -= deltaTime;
	if (worseTime < 0) {
		state = Person::SERIOUS;
		worseTime = worseReferenceTime + Random::Range(-worseTimeOffset, worseTimeOffset);
	}
}
void Person::Die() {
	deathTime -= deltaTime;
	if (deathTime < 0) {
		state = Person::DEATH;
		deathTime = deathReferenceTime + Random::Range(-deathTimeOffset, deathTimeOffset);
	}
}
void Person::BeHospitalized() {
	cureTime -= deltaTime;
	if (cureTime < 0) {
		state = Person::RECOVERY;
		cureTime = cureReferenceTime + Random::Range(-cureTimeOffset, cureTimeOffset);
	}
}
bool Person::IsInfected() {
	return state == Person::INCUBATION || state == Person::CONFIRMED || state == Person::SERIOUS;
}

int Person::incubationReferenceTime = 10;
int Person::incubationTimeOffset = 5;
int Person::worseReferenceTime = 10;
int Person::worseTimeOffset = 5;
int Person::deathReferenceTime = 10;
int Person::deathTimeOffset = 5;
int Person::cureReferenceTime = 10;
int Person::cureTimeOffset = 5;
