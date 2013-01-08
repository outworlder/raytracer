#ifndef QUAD_HPP
#define QUAD_HPP

#include <GL/gl.h>
#include <GL/glu.h>

#include "plane.hpp"

class CQuad : public CPlane {
 protected:
	 Vector L1;
	 Vector L2;
	 float Large(Vector& v1, Vector&v2);
 public:
    virtual bool HasIntersection(CRay& ray, SiData* d);
	 virtual void Draw(void);

	 CQuad(Vector& p, Vector& l1, Vector& l2);
	 ~CQuad();
};
#endif
