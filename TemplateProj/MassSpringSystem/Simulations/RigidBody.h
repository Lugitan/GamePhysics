#pragma once
#include "Simulator.h"
#include "Integrator.h"

class RigidBody
{
public:
	RigidBody();
	RigidBody(Vec3 position, Quat orientation, Vec3 velocity, Vec3 angvelocity, float inv_mass);
	RigidBody(Vec3 position, Vec3 size, int mass, double linearDamping, double angularDamping);
	~RigidBody();

	Vec3 position;					//center of mass
	Quat orientation;				//orientation
	Vec3 velocity;					//Geschwindigkeit
	Vec3 angularVelocity;			//Winkelgeschwindigkeit
	Vec3 angularMomentum;			//Drehimpuls
	Vec3 force;						//Kräfte die auf den körper wirken
	Vec3 torque;					//Rotationskräfte
	float inv_mass;					//Masse
	bool isFixed;
	Mat4 transformMatrix;			//Zum transformieren von world in local Space und andersrum
	Mat4 inv_inertia;				//Trägheitsmoment invers gespeichert da nur invers benötigt

	Real linearDamping;
	Real angularDamping;

	void calculateFixedData();
	void integrate(double timestep);

	void draw(DrawingUtilitiesClass * DUC);
	void addForce(Vec3 force);
	void addForceAtWorldPoint(Vec3 force, Vec3 pos);
	void addForceAtLocalPoint(Vec3 force, Vec3 pos);
private:
	Vec3 size;						//of the box
};


