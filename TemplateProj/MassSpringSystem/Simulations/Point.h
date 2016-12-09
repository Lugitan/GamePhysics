<<<<<<< HEAD
#pragma once
#include "Simulator.h"
class Point
{
public:
	Point();
	Point(Vec3 _position, Vec3 _velocity, Vec3 _force);
	Point(Vec3 _position, Vec3 _velocity, Vec3 _force, float _mass, float _damping);
	~Point();
	Vec3 position;
	Vec3 velocity;
	Vec3 force;
	bool isFixed;
	float mass;
	float damping;
	void draw(DrawingUtilitiesClass * DUC, float size);
	void addForce(Vec3 _force);
	void resetForce();
	Vec3 acceleration;

};

||||||| merged common ancestors
=======
#pragma once
#include "Simulator.h"

class Point
{
public:
	Point();
	Point(Vec3 _position, Vec3 _velocity, Vec3 _force);
	Point(Vec3 _position, Vec3 _velocity, Vec3 _force, float _mass, float _damping);
	~Point();
	Vec3 position;
	Vec3 velocity;
	Vec3 force;
	bool isFixed;
	float mass;
	float damping;
	void draw(DrawingUtilitiesClass * DUC, float size);
	void addForce(Vec3 _force);
	void resetForce();
	Vec3 acceleration;

private:

};

>>>>>>> 51b8ffeb4e66d4b129c02ce699cc599b496f1e0e
