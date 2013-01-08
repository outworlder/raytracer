#ifndef SPHERE_HPP
#define SPHERE_HPP

#include <GL/gl.h>
#include <GL/glu.h>

#include "tracer.hpp"

class CSphere : public CObject {
 protected:
	GLUquadricObj* quadric;
	Vector center;
	float radius;
 public:
    virtual bool HasIntersection(CRay& ray, SiData* d);
	 virtual void Draw(void);

	 CSphere(Vector& p, float r);
	 ~CSphere();
};
#endif
