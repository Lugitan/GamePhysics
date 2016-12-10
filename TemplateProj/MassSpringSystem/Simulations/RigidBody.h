#pragma once
#include "Simulator.h"
#include "Integrator.h"

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
	Vec3 rotation;					//Winkelgeschwindigkeit
	Vec3 acceleration;				//Beschleunigung
	Vec3 oldAcceleration;			//Alte für die Berechnung
	float inv_mass;					//Masse
	bool isFixed;
	Mat4 transformMatrix;			//Zum transformieren von world in local Space und andersrum
	Mat4 inv_inertia;				//Trägheitsmoment invers gespeichert da nur invers benötigt

	Vec3 accumulatedForce;			//in diesem Frame generierte Kräfte
	Vec3 accumulatedTorque;			//in diesem Frame generierter Drehmoment

	Vec3 linearDamping;
	Vec3 angularDamping;

	void calculateFixedData();
	void integrate(double timestep);

	void draw(DrawingUtilitiesClass * DUC);
	void addForce(Vec3 force);
	void addForceAt(Vec3 force, Vec3 pos);
private:
	Vec3 size;						//of the box
};


