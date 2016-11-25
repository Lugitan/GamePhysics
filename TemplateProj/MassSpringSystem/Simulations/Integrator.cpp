#include "Integrator.h"
#include "Point.h"

template<typename context>
Integrator<context>::Integrator()
{
	setIntegrator(0); //EULER
}

template<typename context>
Integrator<context>::~Integrator()
{
}


template<typename context>
void Integrator<context>::setIntegrator(int _method){
	this->method = _method;
}


template<typename context>
Vec3 Integrator<context>::integrate(Vec3 y, float t, float h, fabble f, context* ct){
	switch (method){
	case 1:		// MIDPOINT
		return y + h * f(t + 0.5*h, y + 0.5*h+f(t,y, context),context);
	
	case 2:		// LEAPFROG
		return y + 0,5 * h * (f(t + h, y + h * f(t, y, context), context) + f(t, y, context));
	
	case 0:		// EULER
	default:	
		return y + h * f(t, y, context);
	}
}
