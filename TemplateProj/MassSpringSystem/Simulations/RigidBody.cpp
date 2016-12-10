#include "RigidBody.h"

RigidBody::RigidBody(){
	position		= Vec3(0, 0, 0);
	orientation		= Quat(0, 0, 0, 0);
	velocity		= Vec3(0, 0, 0);
	rotation		= Vec3(0, 0, 0);
	inv_mass		= 0.0;
}

RigidBody::RigidBody(Vec3 _position, Quat _orientation, Vec3 _velocity, Vec3 _angvelocity, float _inv_mass){
	position		= _position;
	orientation		= _orientation;
	velocity		= _velocity;
	rotation		= _angvelocity;
	inv_mass		= _inv_mass;
}

RigidBody::RigidBody(Vec3 _position, Vec3 _size, int _mass) :
	position(_position),
	orientation(Quat(0, 0, 0, 0)),
	velocity(Vec3(0, 0, 0)),
	rotation(Vec3(0, 0, 0)),
	size(_size)
{
	if (_mass <= 0){
		isFixed = true;
		cout << "GRAVITAY";
	}
	else {
		isFixed = false;
		inv_mass = 1 / _mass;
	}
	double x2 = size.x*size.x;
	double y2 = size.y*size.y;
	double z2 = size.z*size.z;
	inv_inertia.initScaling(1/12 * _mass*(y2 + 2), 1/12*_mass*(x2*z2), 1/12*_mass*(x2+y2));
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

void RigidBody::integrate(double timeStep){

	
	Vec3* accel = &acceleration;
	Vec3* vel = &velocity;
	position = Integrator::integrate(position, 0, timeStep, [vel, accel](float h, Vec3 y){
		return Integrator::integrate(*vel, 0, h, [accel](float h, Vec3 y){return *accel; });
	});
	acceleration -= linearDamping*velocity;
	velocity = Integrator::integrate(*vel, 0, timeStep, [accel](float h, Vec3 y){return *accel; });



	if (!isFixed) acceleration += accumulatedForce*1/inv_mass;

	accumulatedForce = Vec3();
}

void RigidBody::addForce(Vec3 force){
	accumulatedForce += force;
}

