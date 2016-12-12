#include "RigidBodySystemSimulator.h"

Gravity gravity = Gravity(Vec3(0, 0, 0));
Real c = 0;

float damp = 1;
ForceRegistry forceRegistry;

//Constructor
RigidBodySystemSimulator::RigidBodySystemSimulator() 
{
	m_iTestCase = 0;
	
	setTestObjects();
}

void RigidBodySystemSimulator::setTestObjects(){
	rbs.clear();
	forceRegistry.clear();
	rbs.push_back(RigidBody(Vec3(0.2, 0, 0), Vec3(0.1, 0.1, 0.1), 1, damp, damp));
	rbs.push_back(RigidBody(Vec3(-0.2, 0, 0), Vec3(0.1, 0.3, 0.1), 1, damp, damp));
	rbs[0].isFixed = true;
	rbs[0].addForce(Vec3(-40, 0, 0));
	rbs[1].addForceAtLocalPoint(Vec3(40, 0, 0), Vec3(0,0.01,0.01));
}

// Functions
const char * RigidBodySystemSimulator::getTestCasesStr(){
	return "Euler, Leapfrog, Midpoint";
}

void RigidBodySystemSimulator::initUI(DrawingUtilitiesClass * DUC) {
	this -> DUC = DUC;
}

void RigidBodySystemSimulator::reset() {
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

void RigidBodySystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext) {
	DUC->setUpLighting(Vec3(0, 0, 0), 0.4*Vec3(1, 1, 1), 2000.0, Vec3(0.5, 0.5, 0.5));
	
	for (size_t i = 0; i < rbs.size(); i++)
	{
		rbs[i].draw(DUC);
	}
}

void RigidBodySystemSimulator::notifyCaseChanged(int testCase) {
	m_iTestCase = testCase;
	switch (m_iTestCase)
	{
	case 0:
		//Euler
		Integrator::setIntegrator(LEAPFROG);
		setTestObjects();
		break;
	case 1:
		//Midpoint
		Integrator::setIntegrator(LEAPFROG);
		setTestObjects();
		break;
	case 2:
		//LeapFrog
		Integrator::setIntegrator(LEAPFROG);
		setTestObjects();
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

int counter = 0;
void checkCollision(RigidBody* a, RigidBody* b){
	CollisionInfo info = checkCollisionSAT(a->transformMatrix, b->transformMatrix);
	if (info.isValid){
		counter = 5;
		Vec3 xa = info.collisionPointWorld - a->position;
		Vec3 xb = info.collisionPointWorld - b->position;
		Vec3 n = info.normalWorld;
		Vec3 velocityApoint = a->velocity + cross(a->angularVelocity, xa);
		Vec3 velocityBpoint = b->velocity + cross(b->angularVelocity, xb);
		Vec3 vrel = velocityApoint - velocityBpoint;

		Real amass = (a->isFixed ? 0 : a->inv_mass);
		Real bmass = (b->isFixed ? 0 : b->inv_mass);
		Mat4 ainertia = a->isFixed ? Mat4() : a->inv_inertia;
		Mat4 binertia = b->isFixed ? Mat4() : b->inv_inertia;

		Real j = dot((-(1. + c))*vrel,n) / (amass +	bmass +
			dot( cross(ainertia.transformVector(cross(xa, n)), xa) +
			  cross(ainertia.transformVector(cross(xb, n)), xb)
			  ,n)
			);

		//cout << "\nSuccess! j:" << j << " \tvrel: " << vrel << "\t n: "<<n << "\t depth: " << info.depth;
		if (j > 0){
			if (!a->isFixed) a->velocity += j*n * a->inv_mass;
			if (!b->isFixed) b->velocity -= j*n * b->inv_mass;

			if (!a->isFixed) a->angularMomentum += cross(xa, j*n);
			if (!b->isFixed) b->angularMomentum -= cross(xb, j*n);
		}
	}
}
void RigidBodySystemSimulator::externalForcesCalculations(float timeElapsed){
	forceRegistry.updateForces(timeElapsed);
	if (true){
		for (size_t i = 0; i < rbs.size(); i++)
		{
			for (size_t j = i+1; j < rbs.size(); j++)
			{
				if (i != j) checkCollision(&rbs[i], &rbs[j]);
			}
		}
	}
	else counter--;
}

void RigidBodySystemSimulator::simulateTimestep(float timeStep) {
	for (size_t i = 0; i < rbs.size(); i++)
	{
		rbs[i].integrate(timeStep);
	}
}

void RigidBodySystemSimulator::onClick(int x, int y){
	m_trackmouse.x += x - m_oldtrackmouse.x;
	m_trackmouse.y += y - m_oldtrackmouse.y;
}

void RigidBodySystemSimulator::onMouse(int x, int y){
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
}

int RigidBodySystemSimulator::getNumberOfRigidBodies() {
	return rbs.size();
}

Vec3 RigidBodySystemSimulator::getPositionOfRigidBody(int i){
	return rbs[i].position;
}

Vec3 RigidBodySystemSimulator::getLinearVelocityOfRigidBody(int i) {
	return rbs[i].velocity;
}

Vec3 RigidBodySystemSimulator::getAngularVelocityOfRigidBody(int i) {
	return rbs[i].angularVelocity;
}

void RigidBodySystemSimulator::applyForceOnBody(int i, Vec3 loc, Vec3 force) {
	rbs[i].addForceAtWorldPoint(force, loc);
}

void RigidBodySystemSimulator::addRigidBody(Vec3 position, Vec3 size, int mass) {
	rbs.push_back(RigidBody(position, size, mass, damp, damp));
}

void RigidBodySystemSimulator::setOrientationOf(int i, Quat orientation) {
	rbs[i].orientation = orientation;
}

void RigidBodySystemSimulator::setVelocityOf(int i, Vec3 velocity) {
	rbs[i].velocity = velocity;
}
