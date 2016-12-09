#pragma once
#include "Simulator.h"

class Integrator
{
public:
	Integrator()	{ setIntegrator(0); /*EULER*/ }
	~Integrator()	{	}
	typedef std::function < Vec3(float t, Vec3 y) > flambda;

	void setIntegrator(int method)	{ this->method = method; };

	Vec3 integrate(Vec3 y, float t, float h, flambda f) {
		switch (method){
		case 2:		// MIDPOINT
			return y + h * f(0.5*h, y + 0.5*h + f(t, y));

		case 1:		// LEAPFROG
			return y + 0.5 * h * (f(h, y + h * f(t, y)) + f(t, y));

		case 0:		// EULER
		default:
			return y + h * f(t, y);
		}
	}

private:
	
	/*
	#define EULER 0
	#define LEAPFROG 1
	#define MIDPOINT 2
	*/
	
	int method;

};


