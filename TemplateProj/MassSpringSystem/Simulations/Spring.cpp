#include "Spring.h"


Spring::Spring()
{
}


Spring::~Spring()
{
}

float Spring::currentLength(){
	Vec3 p = this->point1->position + this->point1->position;
	return sqrtf(powf(p.x, 2) + powf(p.y, 2) + powf(p.z, 2));
}
