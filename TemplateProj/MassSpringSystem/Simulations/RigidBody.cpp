#include "RigidBody.h"

RigidBody::RigidBody(){
	position		= Vec3(0, 0, 0);
	orientation		= Quat(0, 0, 0, 0);
	velocity		= Vec3(0, 0, 0);
	angularVelocity	= Vec3(0, 0, 0);
	inv_mass		= 0.0;
}

RigidBody::RigidBody(Vec3 _position, Quat _orientation, Vec3 _velocity, Vec3 _angvelocity, float _inv_mass){
	position		= _position;
	orientation		= _orientation;
	velocity		= _velocity;
	angularVelocity	= _angvelocity;
	inv_mass		= _inv_mass;
}

RigidBody::RigidBody(Vec3 _position, Vec3 _size, int _mass, double _linearDamping, double _angularDamping) :
	position(_position),
	orientation(Quat(0, 0, 0, 1)),
	velocity(Vec3(0, 0, 0)),
	angularVelocity(Vec3(0, 0, 0)),
	size(_size),
	linearDamping(_linearDamping),
	angularDamping(_angularDamping)
{
	if (_mass <= 0){
		isFixed = true;
	}
	else {
		isFixed = false;
		inv_mass = 1. / _mass;
	}
	double x2 = size.x*size.x;
	double y2 = size.y*size.y;
	double z2 = size.z*size.z;
	inv_inertia.initScaling(1./12 * _mass*(y2 + 2), 1./12*_mass*(x2*z2), 1./12*_mass*(x2+y2));
	inv_inertia = inv_inertia.inverse();
}

RigidBody::~RigidBody(){
}

void RigidBody::draw(DrawingUtilitiesClass * DUC){
	Mat4 out;
	out.initScaling(size.x, size.y, size.z);
	out *= orientation.getRotMat();
	out.value[3][0] = position.x;
	out.value[3][1] = position.y;
	out.value[3][2] = position.z;
	DUC->drawRigidBody(out);
}

void calculateTransformMatrix(Mat4 &transformMatrix, const Vec3 &pos, const Quat &otn){	
	transformMatrix.initTranslation(pos.x, pos.y, pos.z);
	transformMatrix += otn.getRotMat();
}

void RigidBody::calculateFixedData(){
	calculateTransformMatrix(transformMatrix, position, orientation);
}

Real damp(Real a, Real v, Real damp, Real inv_mass){
	if (a == 0) return 0;
	Real newA = a - damp*v*inv_mass;
	if (abs(a) + abs(newA) > abs(a + newA)) return 0;
	return newA;
}

void RigidBody::integrate(double timeStep){

	
	position += timeStep*velocity;
	velocity += timeStep*(force / inv_mass);

	orientation += timeStep / 2 * Quat(0, angularVelocity.x, angularVelocity.y, angularVelocity.z)*orientation;

	angularMomentum += timeStep*torque;
	Mat4 ortTransposed = orientation.getRotMat();
	Mat4 curr_inv_inertia = ortTransposed*inv_inertia;
	ortTransposed.transpose();
	curr_inv_inertia *= ortTransposed;
	angularVelocity = curr_inv_inertia * angularMomentum;
	
	force = Vec3();
	torque = Vec3();

	cout << orientation << angularVelocity << "\n";
	
}

void RigidBody::addForce(Vec3 _force){
	force += _force;
}

void RigidBody::addForceAtWorldPoint(Vec3 _force, Vec3 pos){
	pos -= position;
	addForceAtLocalPoint(_force, position);
}

void RigidBody::addForceAtLocalPoint(Vec3 _force, Vec3 pos){
	torque += cross(pos, _force);
	force += _force;
}

