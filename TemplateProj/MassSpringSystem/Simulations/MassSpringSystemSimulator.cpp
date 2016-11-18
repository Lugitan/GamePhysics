#include "MassSpringSystemSimulator.h";

//Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	m_iTestCase = 0;
	Point p1 = Point(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0));
	Point p2 = Point(Vec3(0.5, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0));
	Point p3 = Point(Vec3(0, 0.5, 0), Vec3(0, 0, 0), Vec3(0, 0, 0));
	Point p4 = Point(Vec3(0, 0, 0.5), Vec3(0, 0, 0), Vec3(0, 0, 0));
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);
	springs.push_back(Spring(&points[0], &points[1], 0, 0));
	springs.push_back(Spring(&points[0], &points[2], 0, 0));
	springs.push_back(Spring(&points[0], &points[3], 0, 0));
	springs.push_back(Spring(&points[3], &points[2], 0, 0));
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
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].draw(DUC, 0.01);
	}
	
	for (size_t i = 0; i < springs.size(); i++)
	{
		springs[i].draw(DUC);
	}
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
void MassSpringSystemSimulator::simulateTimestep(float timeStep){
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].resetForce();
		points[i].addForce(Vec3(0, 0, 9.81)*points[i].mass);
	}
	for (size_t i = 0; i < springs.size(); i++)
	{
		Vec3 force = springs[i].computeElasticForces();
		springs[i].point1->addForce(force);
		springs[i].point1->addForce(-force);
	}
	//TODO: Calculate new Position and Velocity
}
void MassSpringSystemSimulator::onClick(int x, int y){}
void MassSpringSystemSimulator::onMouse(int x, int y){}

// Specific Functions
void MassSpringSystemSimulator::setIntegrator(int integrator){}
void MassSpringSystemSimulator::setMass(float mass){
	m_fMass = mass;
}
void MassSpringSystemSimulator::setStiffness(float stiffness){
	m_fStiffness = stiffness;
}
void MassSpringSystemSimulator::setDampingFactor(float damping){
	m_fDamping = damping;
}
int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed){
	Point p = Point(position, Vec3(0, 0, 0), Velocity, m_fMass, m_fDamping);//Potential source of err if assumptions how it works are wrong
	p.isFixed = isFixed;
	points.push_back(p);
	
	return -1;
}
void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength){
	springs.push_back(Spring(&points[masspoint1], &points[masspoint2], m_fStiffness, initialLength));
}
int MassSpringSystemSimulator::getNumberOfMassPoints(){
	return points.size();
}
int MassSpringSystemSimulator::getNumberOfSprings(){
	return springs.size();
}
Vec3 MassSpringSystemSimulator::getPositionOfMassPoint(int index){
	return points[index].position;
}
Vec3 MassSpringSystemSimulator::getVelocityOfMassPoint(int index){
	return points[index].velocity;
}
void MassSpringSystemSimulator::applyExternalForce(Vec3 force){
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].force += force;
	}
}
