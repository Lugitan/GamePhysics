#pragma once
#include "Simulator.h"


class RigidBodySystem
{
public: 
	//All Variables from the Slides und mehr
	Vec3 orientation; //orientation
	Vec3 f;			//force
	Vec3 cM;		//center of mass
	Vec3 size;		//of the box
	Vec3 torque;	//Drehmoment
	Vec3 L;		    //Drehimpuls
	Vec3 w;			//Winkelgeschwindigkeit
	float I;		//Trägheitstensor
	int mass;		//Masse

	RigidBodySystem();
	RigidBodySystem(Vec3 _cM, Vec3 _size, Vec3 _orientation, Vec3 _force);
	RigidBodySystem(Vec3 _cM, Vec3 _size, Vec3 _orientation, Vec3 _force, int _mass);
	~RigidBodySystem();

	void draw(DrawingUtilitiesClass * DUC, Mat4 worldSpaceMatrix);

private:
	//Vec3 position;
};