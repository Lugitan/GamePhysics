#pragma once
#include "Simulator.h"

template <class context>
class Integrator
{
public:
	Integrator();
	~Integrator();
	
	typedef Vec3 (*fabble)(float t, Vec3 y, context* ct);

	void setIntegrator(int method);
	Vec3 integrate(Vec3 y, float t, float h, fabble f, context* ct); 

private:
	
	/*
	#define EULER 0
	#define LEAPFROG 1
	#define MIDPOINT 2
	*/
	
	int method;

};


