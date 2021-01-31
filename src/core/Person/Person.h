#pragma once
#include "vector.h"
#include "Maths.h"
#include "Random.h"

#include <glm/glm.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Person {
public:
	enum State { NORMAL, INCUBATION, CONFIRMED, SERIOUS, DEATH, RECOVERY } state;
	vector pos;
	glm::mat4 trans;
	glm::vec3 direction;
	int lastCollider;
	Person(vector initialPos, State initialState);
	void BeConfirmed();
	void BeSerious();
	void Die();
	void BeHospitalized();
	bool IsInfected();
private:
	float incubationTime;
	static int incubationTimeOffset;
	static int incubationReferenceTime;
	float worseTime;
	static int worseTimeOffset;
	static int worseReferenceTime;
	float deathTime;
	static int deathTimeOffset;
	static int deathReferenceTime;
	float cureTime;
	static int cureTimeOffset;
	static int cureReferenceTime;
};
