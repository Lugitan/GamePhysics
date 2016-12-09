#include "RigidBody.h"

RigidBody::RigidBody(){
	position		= Vec3(0, 0, 0);
	orientation		= Quat(0, 0, 0, 0);
	velocity		= Vec3(0, 0, 0);
	angvelocity		= Vec3(0, 0, 0);
	inv_mass		= 0.0;
}

RigidBody::RigidBody(Vec3 _position, Quat _orientation, Vec3 _velocity, Vec3 _angvelocity, float _inv_mass){
	position		= _position;
	orientation		= _orientation;
	velocity		= _velocity;
	angvelocity		= _angvelocity;
	inv_mass		= _inv_mass;
}

RigidBody::RigidBody(Vec3 _position, Vec3 _size, int _mass){
	position		= _position;
	orientation		= Quat(0, 0, 0, 0);
	velocity		= Vec3(0, 0, 0);
	angvelocity		= Vec3(0, 0, 0);
	inv_mass		= 1 / _mass;
}

RigidBody::~RigidBody(){
}

void draw(DrawingUtilitiesClass * DUC){
	DUC->drawRigidBody(Mat4(1.,0.,0.,0.,  
							0.,1.,0.,0.,  
							0.,0.,1.,0.,  
							0.,0.,0.,1.));
}