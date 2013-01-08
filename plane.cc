#include "plane.hpp"

#include <iostream>

bool CPlane::HasIntersection(CRay& ray, SiData* d) {
	//t = -(N·D)/(N·(P0 - P2))
	if (Normal*(ray.Origin()-P) == 0) return false;
	float t = -(Normal*ray.Direction())/(Normal*(ray.Origin()-P));
	
	if (t<0.0001f)
		return false;
	
	d->Normal=Normal;
	-d->Normal;
	d->t=t;
	d->Object=this;
	Vector p(ray.AtPos(t));
	d->Position=p;
	return true;
}


CPlane::CPlane(Vector& p, Vector normal):CObject() {
	P=p;
	Normal=normal;
	Normal.Normalize();
}

CPlane::~CPlane() {
}

void CPlane::Draw(void) {
}
