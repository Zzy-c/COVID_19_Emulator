#pragma once
#include <iostream>
#include "Person.h"
#include "data.h"

class Hospital {
public:
	static int capacity;
	static int size;
	static bool isInHospital[2000];
	static void Run();
	static bool Full();
};