#include "Simulator.h"
#include "RigidBody.h"
/*
Forces are registered in the ForceRegistry and can be applied over one simple call of updateForces(timestep)
*/


class ForceGenerator{
public:
	virtual void updateForce(RigidBody *body, double duration) = 0;
};

class Gravity : public ForceGenerator{
	Vec3 gravity;
public:
	Gravity(const Vec3 &gravity);
	virtual void updateForce(RigidBody *body, double duration);
};

class Spring : public ForceGenerator{
	Vec3 connectionPoint;
	Vec3 otherConnectionPoint;
	RigidBody *other;
	double stiffness;
	double restLength;

public:

	Spring(const Vec3 &localConnectionPt,
		RigidBody *other,
		const Vec3 &otherConnectionPt,
		double springConstant,
		double restLength);
	virtual void updateForce(RigidBody *body, double duration);
};

class ForceOverTimeAt : public ForceGenerator{
	ForceOverTimeAt(Real _time, Real _until, Vec3 _force, Vec3 _at);
	Real from;
	Real time;
	Real until;
	Vec3 force;
	Vec3 at;

	virtual void updateForce(RigidBody *body, double duration);
};

class ForceRegistry{
private:
	// Keeps track of one force generator and the body it applies to.
	struct ForceRegistration{
		RigidBody *body;
		ForceGenerator *fg;
	};
	// Holds the list of registrations.
	typedef std::vector<ForceRegistration> Registry;
	Registry registrations;

public:
	void add(RigidBody* body, ForceGenerator *fg);
	void remove(RigidBody* body, ForceGenerator *fg);
	void clear();
	void updateForces(double duration);
};

