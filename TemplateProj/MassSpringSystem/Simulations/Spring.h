#pragma once
#include "Point.h";
#include "Simulator.h"
class Spring
{
public:
	Spring();
	~Spring();
	Point* point1;
	Point* point2;
	float stiffness;
	float initialLength;
	float currentLength();
};

