#include "ForceGenerator.h"

void ForceRegistry::updateForces(double duration){
	for (size_t i = 0; i < registrations.size(); i++)	{
		registrations[i].fg->updateForce(registrations[i].body, duration);
	}
}

void ForceRegistry::add(RigidBody *body, ForceGenerator *fg)
{
	ForceRegistry::ForceRegistration registration;
	registration.body = body;
	registration.fg = fg;
	registrations.push_back(registration);
}

void ForceRegistry::clear(){
	registrations.clear();
}

Gravity::Gravity(const Vec3& gravity) : gravity(gravity){}

void Gravity::updateForce(RigidBody* body, double duration)
{
cout << "GRAVITAY";
	// Check that we do not have infinite mass
	if(body->isFixed) return;
	// Apply the mass-scaled force to the body
	body->addForce(gravity * body->inv_mass);
}

Spring::Spring(const Vec3 &localConnectionPt,
	RigidBody *other,
	const Vec3 &otherConnectionPt,
	double stiffness,
	double restLength)
	: connectionPoint(localConnectionPt),
	otherConnectionPoint(otherConnectionPt),
	other(other),
	stiffness(stiffness),
	restLength(restLength)
{}

void Spring::updateForce(RigidBody* body, double duration)
{
	//TODO
}