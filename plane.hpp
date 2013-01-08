#ifndef PLANE_HPP
#define PLANE_HPP

#include <GL/gl.h>
#include <GL/glu.h>

#include "tracer.hpp"

class CPlane : public CObject {
 protected:
	 Vector P;
	 Vector Normal;
 public:
    virtual bool HasIntersection(CRay& ray, SiData* d);
	 virtual void Draw(void);

	 CPlane(Vector& p, Vector Normal);
	 ~CPlane();
};
#endif
