#pragma once
#include "Point.h";
#include "Simulator.h"
class Spring
{
public:
	Spring();
	~Spring();
	Spring(Point* p1, Point* p2, float _stiffness, float _initialLength);
	Point* point1;
	Point* point2;
	float stiffness;
	float initialLength;
	float currentLength();
	void draw(DrawingUtilitiesClass * DUC);
};

