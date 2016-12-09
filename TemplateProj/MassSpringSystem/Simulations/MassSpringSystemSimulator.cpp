<<<<<<< HEAD
#include "MassSpringSystemSimulator.h";

const float GRAVITY = -0.001;
float stiffness = 40;
float mass = 10;
float initialLength = 5;
int damping = 0;


//Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	m_iTestCase = 0;
	method = EULER;
	setMass(mass);
	setStiffness(stiffness);
	setDampingFactor(damping);

	Point p1 = Point(Vec3(0, 2, 0.1), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);
	Point p2 = Point(Vec3(0, 2.2, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);
	
	points.push_back(p1);
	points.push_back(p2);

	springs.push_back(Spring(&points[0], &points[1], m_fStiffness, initialLength));
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
	/*old variant
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].resetForce();
		points[i].addForce(Vec3(0, GRAVITY, 0)*points[i].mass);
	}
	for (size_t i = 0; i < springs.size(); i++)
	{
		Vec3 force = springs[i].computeElasticForces();
		springs[i].point1->addForce(-force);
		springs[i].point1->addForce(force);
	}*/


	integratePositions(timeStep);
	integrateVelocity(timeStep);
	integrateAccerleration(timeStep); //new variant
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
		points[i].addForce(force);
	}
}

void MassSpringSystemSimulator::integratePositions(float timeStep){
	switch (method)
	{
	case EULER:
		for (size_t i = 0; i < points.size(); i++)
		{
			points[i].position = points[i].position + timeStep*points[i].velocity;
			if (points[i].position.y <= 0){
				points[i].position.y = 0.00000001;
			}
		}
		break;
	default:
		break;
	}
}

void MassSpringSystemSimulator::integrateVelocity(float timeStep){
	switch (method)
	{
	case EULER:
		for (size_t i = 0; i < points.size(); i++)
		{
			points[i].acceleration -= points[i].velocity*m_fDamping;
			points[i].velocity = points[i].velocity + timeStep*points[i].acceleration;
			if (points[i].position.y <= 0){
				points[i].velocity.y = 0;
			}
		}
		break;
	default:
		break;
	}
}

//TODO needs to be implemented, use formula of internal and external Force
void MassSpringSystemSimulator::integrateAccerleration(float timeStep) {

}


||||||| merged common ancestors
=======
#include "MassSpringSystemSimulator.h";

//const float GRAFITY = -0.001;
const Vec3 GRAVITY = Vec3(0, -9.81, 0);
float stiffness = 40;
float mass = 1;
float initialLength = 0.1;
float damping = 0.25;
Integrator<Point> integrator;

//Construtors
MassSpringSystemSimulator::MassSpringSystemSimulator()
{
	m_iTestCase = 0;
	
	integrator.setIntegrator(LEAPFROG);
	setMass(mass);
	setStiffness(stiffness);
	setDampingFactor(damping);

	setObjectsInScene();
}

// Functions
const char * MassSpringSystemSimulator::getTestCasesStr(){ 
	return "Euler, Leapfrog, Midpoint";
}

//In this functions all the points and srpings in the scene are set
void MassSpringSystemSimulator::setObjectsInScene(){
	Point p1 = Point(Vec3(0, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);
	Point p2 = Point(Vec3(0.3, 0, 0), Vec3(0, 0, 0), Vec3(0, 0, 0), m_fMass, m_fDamping);

	p1.isFixed = true;

	points.push_back(p1);
	points.push_back(p2);

	springs.push_back(Spring(&points[0], &points[1], m_fStiffness, initialLength));
}

//Draw the Components of the UI, see TemplateSimulator for adding Components to the UI
void MassSpringSystemSimulator::initUI(DrawingUtilitiesClass * DUC){
	this -> DUC = DUC;
}

//reset mouse positions
void MassSpringSystemSimulator::reset(){
	m_mouse.x = m_mouse.y = 0;
	m_trackmouse.x = m_trackmouse.y = 0;
	m_oldtrackmouse.x = m_oldtrackmouse.y = 0;
}

//This functions draws the points and the spring connections between these points
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

//This functions deals with all the necessary changes to the scene, if the testcase (method) has changed
void MassSpringSystemSimulator::notifyCaseChanged(int testCase){

	points.clear();

	m_iTestCase = testCase;
	switch (m_iTestCase)
	{
	case 0:
		//Euler
		integrator.setIntegrator(LEAPFROG);
		setObjectsInScene();
		break;
	case 1:
		//Midpoint
		integrator.setIntegrator(LEAPFROG);
		setObjectsInScene();
		break;
	case 2:
		//LeapFrog
		integrator.setIntegrator(LEAPFROG);
		setObjectsInScene();
		break;
	default:
		cout << "Empty Test!\n";
		break;
	}
}

//Here the external forces (mouse click) are applied
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

//This function is called for every timestep set in the main.cpp to calculate the new values
void MassSpringSystemSimulator::simulateTimestep(float timeStep){
	integratePositions(timeStep);
	integrateVelocity(timeStep);
	integrateAcceleration(timeStep);	//>>>>>>>>> PUT LOOPS INSTEAD OF FUNCTIONS <<<<<<<<<<
}

//These functions handle the mouse input
void MassSpringSystemSimulator::onClick(int x, int y){
	m_trackmouse.x += x - m_oldtrackmouse.x;
	m_trackmouse.y += y - m_oldtrackmouse.y;
}
void MassSpringSystemSimulator::onMouse(int x, int y){
	m_oldtrackmouse.x = x;
	m_oldtrackmouse.y = y;
}

//This function set the necessary value for the calculation steps
void MassSpringSystemSimulator::setIntegrator(int _integrator){
	integrator.setIntegrator(_integrator);
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
void MassSpringSystemSimulator::addSpring(int masspoint1, int masspoint2, float initialLength){
	springs.push_back(Spring(&points[masspoint1], &points[masspoint2], m_fStiffness, initialLength));
}

//What does this function do again?
int MassSpringSystemSimulator::addMassPoint(Vec3 position, Vec3 Velocity, bool isFixed){
	Point p = Point(position, Vec3(0, 0, 0), Velocity, m_fMass, m_fDamping);//Potential source of err if assumptions how it works are wrong
	p.isFixed = isFixed;
	points.push_back(p);
	
	return -1;
}

//Return functions
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

//This function applies the new forces after they have been calculated for the new time step
void MassSpringSystemSimulator::applyExternalForce(Vec3 force){
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].addForce(force);
	}
}

//The fuck are those again?
Vec3 ivel(float t, Vec3 y, Point* ct){ 
	return ct->acceleration; 
}
Vec3 ipos(float h, Vec3 y, Point* ct){ 
	return integrator.integrate(ct->velocity, 0, h, *ivel, ct);
}

//Somehow the new positions are calculated here
void MassSpringSystemSimulator::integratePositions(float timeStep){
	for (size_t i = 0; i < points.size(); i++)
	{
		if (!points[i].isFixed)
			points[i].position = integrator.integrate(points[i].position, 0, timeStep, *ipos, &points[i]);
		
		if (points[i].position.y < -0.5)
			points[i].position.y = 0.000001;
	}
}

//The velocity is calculated here apperently
void MassSpringSystemSimulator::integrateVelocity(float timeStep){
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].acceleration -= points[i].damping*points[i].velocity;
		points[i].velocity = integrator.integrate(points[i].velocity, 0, timeStep, *ivel, &points[i]);
	}
}

//Same goes for the acceleration
void MassSpringSystemSimulator::integrateAcceleration(float timeStep){
	for (size_t i = 0; i < points.size(); i++)
	{
		points[i].acceleration = GRAVITY; 
	}

	for (size_t j = 0; j < springs.size(); j++)
	{
		Vec3 force = springs[j].computeElasticForces();
		springs[j].point1->acceleration += force / springs[j].point1->mass;
		springs[j].point2->acceleration -= force / springs[j].point2->mass;
	}
}


>>>>>>> 51b8ffeb4e66d4b129c02ce699cc599b496f1e0e
