#include "RigidBodySystemSimulator.h"
RigidBodySystem rbs;

//Constructor
RigidBodySystemSimulator::RigidBodySystemSimulator() {
	rbs = RigidBodySystem::RigidBodySystem();
}

void RigidBodySystemSimulator::setObjectsInScene() {

}
	

void RigidBodySystemSimulator::initUI(DrawingUtilitiesClass *DUC) {
	this->DUC = DUC;
}

void RigidBodySystemSimulator::reset() {

}

void RigidBodySystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext) {

	//Beispiel um einen Rigidbody zu zeichnen. Matrix muss noch berechnet werden.
	/*DUC->setUpLighting(Vec3(0,0,0),0.4*Vec3(1,1,1),2000.0, Vec3(0.5,0.5,0.5)); 
	BodyA.Obj2WorldMatrix = BodyA.scaleMat * BodyA.rotMat * BodyA.translatMat;
	DUC->drawRigidBody(BodyA.Obj2WorldMatrix);*/

	//Matrix calculation here
	GamePhysics::Mat4 worldMatrix = (0, 0, 0, 0, 
									 0, 0, 0, 0,
									 0, 0, 0, 0,
									 0, 0, 0, 0);

	rbs.draw(DUC, worldMatrix);
}

void RigidBodySystemSimulator::notifyCaseChanged(int testCase) {

}

void RigidBodySystemSimulator::externalForcesCalculations(float timeElapsed){

}

void RigidBodySystemSimulator::simulateTimestep(float timeStep) {

}

void RigidBodySystemSimulator::onClick(int x, int y){

}

void RigidBodySystemSimulator::onMouse(int x, int y){

}

int RigidBodySystemSimulator::getNumberOfRigidBodies() {
	return 0;
}

Vec3 RigidBodySystemSimulator::getPositionOfRigidBody(int i){
	return Vec3(0, 0, 0);
}

Vec3 RigidBodySystemSimulator::getLinearVelocityOfRigidBody(int i) {
	return Vec3(0, 0, 0);
}

Vec3 RigidBodySystemSimulator::getAngularVelocityOfRigidBody(int i) {
	return Vec3(0, 0, 0);
}

void RigidBodySystemSimulator::applyForceOnBody(int i, Vec3 loc, Vec3 force) {

}

void RigidBodySystemSimulator::addRigidBody(Vec3 position, Vec3 size, int mass) {

}

void RigidBodySystemSimulator::setOrientationOf(int i, Quat orientation) {

}

void RigidBodySystemSimulator::setVelocityOf(int i, Vec3 velocity) {

}
