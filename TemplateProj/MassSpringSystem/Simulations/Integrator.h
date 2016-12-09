#pragma once
#include "Simulator.h"

template <class context>
class Integrator
{
public:
	Integrator()	{ setIntegrator(0); /*EULER*/ }
	~Integrator()	{	}

	//this vector defines the function used for the velocity
	typedef Vec3 (*func_ableitung)(float t, Vec3 y, context* ct);

	void setIntegrator(int method)	{ this->method = method; };
	
	//Here the new positions are calculated with the respective methods used
	Vec3 integrate(Vec3 y, float t, float h, func_ableitung f, context* ct) {
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


