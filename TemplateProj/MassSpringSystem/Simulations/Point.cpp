#include "Point.h"


Point::Point()
{
	position = Vec3(0,0,0);
	velocity = Vec3(0, 0, 0);
	force = Vec3(0, 0, 0);
}

Point::Point(Vec3 _position, Vec3 _velocity, Vec3 _force)
{
	position = _position;
	velocity = _velocity;
	force = _force;
}

Point::~Point()
{
}

void Point::draw(DrawingUtilitiesClass * DUC, float size){
	DUC->drawSphere(position, Vec3(size,size,size));
}
