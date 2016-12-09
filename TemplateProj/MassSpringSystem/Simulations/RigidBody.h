#pragma once
#include "Simulator.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(Vec3 position, Quat orientation, Vec3 velocity, Vec3 angvelocity, float inv_mass);
	RigidBody(Vec3 position, Vec3 size, int mass);
	~RigidBody();

	Vec3 position;					//center of mass
	Quat orientation;				//orientation
	Vec3 velocity;					//Geschwindigkeit
	Vec3 angvelocity;				//Winkelgeschwindigkeit
	float inv_mass;					//Masse
	
	void draw(DrawingUtilitiesClass * DUC);

private:
	Vec3 size;						//of the box
};


