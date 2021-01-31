#include "Hospital.h"

int Hospital::capacity = 100;
int Hospital::size = 0;
bool Hospital::isInHospital[2000];

void Hospital::Run() {
	for (int i = 0; i < total; i++) {
		if (isInHospital[i]) {
			person[i]->BeHospitalized();
			if (person[i]->state == Person::RECOVERY) {
				isInHospital[i] = false;
				size--;
			}
		}
	}
}

bool Hospital::Full() {
	return size == capacity;
}