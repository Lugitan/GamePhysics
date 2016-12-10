#include "MassSpringSystemSimulator.h"

const float GRAFITY = -0.001;
const Vec3 GRAVITY = Vec3(0, -9.81, 0);
float stiffness = 40;
float mass = 1;
float initialLength = 0.1;
float damping = 0.25;

//Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	m_iTestCase = 0;
	
	Integrator::setIntegrator(LEAPFROG);
	setMass(mass);
	setStiffness(stiffness);
	setDampingFactor(damping);
	setStuffUp();
	
}

void MassSpringSystemSimulator::setStuffUp(){
	points.clear();
	springs.clear();
	Point p1 = Point(Vec3(0, 5, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);
	Point p2 = Point(Vec3(1, 5, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);
	Point p3 = Point(Vec3(2, 5, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);
	Point p4 = Point(Vec3(3, 5, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);
	p1.isFixed = true;
	points.push_back(p1);
	points.push_back(p2);
	points.push_back(p3);
	points.push_back(p4);

	springs.push_back(Spring(&points[0], &points[1], m_fStiffness, initialLength));
	springs.push_back(Spring(&points[1], &points[2], m_fStiffness, initialLength));
	springs.push_back(Spring(&points[2], &points[3], m_fStiffness, initialLength));
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

void MassSpringSystemSimulator::notifyCaseChanged(int testCase){

	m_iTestCase = testCase;
	switch (m_iTestCase)
	{
	case 0:
		//Euler
		Integrator::setIntegrator(LEAPFROG);
		setStuffUp();
		break;
	case 1:
		//Midpoint
		Integrator::setIntegrator(LEAPFROG);
		setStuffUp();
		break;
	case 2:
		//LeapFrog
		Integrator::setIntegrator(LEAPFROG);
		setStuffUp();
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

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
		float speedScale = 0.001f;
		for (size_t i = 0; i < points.size(); i++)
		{
			points[i].position += speedScale * (float)m_trackmouse.x * camRightWorld;
			points[i].position += -speedScale * (float)m_trackmouse.y * camUpWorld;
		}

		// Reset accumulated mouse deltas
		m_trackmouse.x = m_trackmouse.y = 0;
	}
}


void MassSpringSystemSimulator::simulateTimestep(float timeStep){
	for (size_t i = 0; i < points.size(); i++)
	{

		Vec3* v = &points[i].velocity;
		Vec3* a = &points[i].acceleration;
		if (!points[i].isFixed){
			auto f = [v, a](float h, Vec3 y){
				return Integrator::integrate(*v, 0, h, [a](float h, Vec3 y){return *a; });
			};
			points[i].position = Integrator::integrate(points[i].position, 0, timeStep, f);
		}
		if (points[i].position.y < 0.)
			points[i].position.y = 0.000001;

		points[i].acceleration -= points[i].damping*points[i].velocity;
		points[i].velocity = Integrator::integrate(points[i].velocity, 0, timeStep, [a](float h, Vec3 y){return *a; });
	}
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].acceleration = GRAVITY;
	}
	for (size_t j = 0; j < springs.size(); j++)
	{
		Vec3 foas = springs[j].computeElasticForces();
		springs[j].point1->acceleration += foas / springs[j].point1->mass;
		springs[j].point2->acceleration -= foas / springs[j].point2->mass;
	}
}


void MassSpringSystemSimulator::onClick(int x, int y){
	m_trackmouse.x += x - m_oldtrackmouse.x;
	m_trackmouse.y += y - m_oldtrackmouse.y;
}
void MassSpringSystemSimulator::onMouse(int x, int y){
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
}

// Specific Functions
void MassSpringSystemSimulator::setIntegrator(int _integrator){
	Integrator::setIntegrator(_integrator);
}
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
		points[i].addForce(force);
	}
}

