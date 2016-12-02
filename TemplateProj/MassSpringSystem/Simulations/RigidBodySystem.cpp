#include "RigidBodySystem.h"

RigidBodySystem::RigidBodySystem() {
	orientation = Vec3(0, 0, 0);
	f = Vec3(0, 0, 0);
	cM = Vec3(0, 0, 0);
	size = Vec3(0, 0, 0);
}

RigidBodySystem::RigidBodySystem(Vec3 _cM, Vec3 _size, Vec3 _orientation, Vec3 _force) {
	orientation = _orientation;
	f = _force;
	cM = _cM;
	size = _size;
}

RigidBodySystem::RigidBodySystem(Vec3 _cM, Vec3 _size, Vec3 _orientation, Vec3 _force, int _mass) {
	orientation = _orientation;
	f = _force;
	cM = _cM;
	size = _size;
	mass = _mass;
}

RigidBodySystem::~RigidBodySystem() {}

void RigidBodySystem::draw(DrawingUtilitiesClass * DUC, Mat4 worldSpaceMatrix) {
	DUC->drawRigidBody(worldSpaceMatrix);
}