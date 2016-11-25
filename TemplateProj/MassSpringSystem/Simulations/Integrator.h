#pragma once
#include "Simulator.h"

template <class context>
class Integrator
{
public:
	Integrator()	{ setIntegrator(0); /*EULER*/ }
	~Integrator()	{	}

	
	typedef Vec3 (*fabble)(float t, Vec3 y, context* ct);

	void setIntegrator(int method)	{ this->method = method; };
	
	Vec3 integrate(Vec3 y, float t, float h, fabble f, context* ct) {
		switch (method){
		case 2:		// MIDPOINT
			return y + h * f(0.5*h, y + 0.5*h + f(t, y, ct), ct);

		case 1:		// LEAPFROG
			return y + 0.5 * h * (f(h, y + h * f(t, y, ct), ct) + f(t, y, ct));

		case 0:		// EULER
		default:
			return y + h * f(t, y, ct);
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


