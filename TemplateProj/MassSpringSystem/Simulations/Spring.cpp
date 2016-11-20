#include "Spring.h"


Spring::Spring()
{
}
Spring::Spring(Point* p1, Point* p2, float _stiffness, float _initialLength)
{
	point1 = p1;
	point2 = p2;
	stiffness = _stiffness;
	initialLength = _initialLength;
}

Spring::~Spring()
{
}

float Spring::currentLength(){
	Vec3 p = point1->position + point2->position;
	return sqrtf(powf(p.x, 2) + powf(p.y, 2) + powf(p.z, 2));
}

void Spring::draw(DrawingUtilitiesClass * DUC){
	DUC->beginLine();
	DUC->drawLine(point1->position, Vec3(1,1,1), point2->position, Vec3(1,1,1));
	DUC->endLine();
}

Vec3 Spring::computeElasticForces(){
	return (-stiffness)*(currentLength() - initialLength)*(point1->position - point2->position) / currentLength();
}

