#include "MassSpringSystemSimulator.h";

//Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	m_iTestCase = 0;
}

// Functions
const char * MassSpringSystemSimulator::getTestCasesStr(){ 
	return "Euler, Leapfrog, Midpoint"; 
}

void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC){
	this -> DUC = DUC;
}
void MassSpringSystemSimulator::reset(){
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}
void MassSpringSystemSimulator::drawFrame(ID3D11DeviceContext* pd3dImmediateContext){
	DUC->setUpLighting(Vec3(), 0.4*Vec3(1, 1, 1), 100, 0.6*Vec3(0.97, 0.86, 1));
	DUC->beginLine();
	DUC->drawLine(Vec3(-0.5, 0, 0), Vec3(1,0,0), Vec3(0.5, 0, 0), Vec3(0,0,1));
	DUC->endLine();
	DUC->drawSphere(Vec3(-0.5, 0, 0), Vec3(0.1, 0.1, 0.1));
	DUC->drawSphere(Vec3(0.5, 0, 0), Vec3(0.1, 0.1, 0.1));
}

void MassSpringSystemSimulator::notifyCaseChanged(int testCase){}

void MassSpringSystemSimulator::externalForcesCalculations(float timeElapsed){
	// Apply accumulated mouse deltas to g_vfMovableObjectPos (move along cameras view plane)
	if (m_trackmouse.x != 0 || m_trackmouse.y != 0)
	{
		// Calcuate camera directions in world space
		Mat4 m = Mat4(DUC->g_camera.GetViewMatrix());
		m = m.inverse();
		Vec3 camRightWorld = Vec3(g_XMIdentityR0);
		camRightWorld = m.transformVectorNormal(camRightWorld);
		Vec3 camUpWorld = Vec3(g_XMIdentityR1);
		camUpWorld = m.transformVectorNormal(camUpWorld);

		// Add accumulated mouse deltas to movable object pos

		/*float speedScale = 0.001f;
		m_vfMovableObjectPos += speedScale * (float)m_trackmouse.x * camRightWorld;
		m_vfMovableObjectPos += -speedScale * (float)m_trackmouse.y * camUpWorld;
*/

		// Reset accumulated mouse deltas
		m_trackmouse.x = m_trackmouse.y = 0;
	}
}
void MassSpringSystemSimulator::simulateTimestep(float timeStep){}
void MassSpringSystemSimulator::onClick(int x, int y){}
void MassSpringSystemSimulator::onMouse(int x, int y){}

// Specific Functions
void MassSpringSystemSimulator::setIntegrator(int integrator){}
void MassSpringSystemSimulator::setMass(float mass){}
void MassSpringSystemSimulator::setStiffness(float stiffness){}
void MassSpringSystemSimulator::setDampingFactor(float damping){}
int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed){
	return -1;
}
void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength){}
int MassSpringSystemSimulator::getNumberOfMassPoints(){
	return -1;
}
int MassSpringSystemSimulator::getNumberOfSprings(){
	return -1;
}
Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index){
	return Vec3(0, 0, 0);
}
Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index){
	return Vec3(0, 0, 0);
}
void MassSpringSystemSimulator::applyExternalForce(Vec3 force){}
