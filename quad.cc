#include "quad.hpp"

#include <iostream>

float CQuad::Large(Vector& v1, Vector& v2) {
	float temp1, temp2;
	temp1=v1*v2;
	temp2=v2*v1;
	return (temp1>temp2) ?  temp1 : temp2;
	
}

bool CQuad::HasIntersection(CRay& ray, SiData* d) {
	//t = -(N·D)/(N·(P0 - P2))
	if (Normal*(ray.Origin()-P) == 0) return false;
	float t = -(Normal*ray.Direction())/(Normal*(ray.Origin()-P));
	
	if (t<0.0f)
		return false;
	
	Vector p(ray.AtPos(t));
	
	Vector M(p-P);
	float V1=Large(M,L2);
	float V2=Large(L1,M);
	float Area=Large(L1,L2);
	float u=V1/Area;
	float v=V2/Area;
	if ((0 <= v) && (0 <= v <= 1)) {
		d->Normal=Normal;
		-d->Normal;
		d->t=t;
		d->Object=this;
		d->Position=p;
		return true;
	} else {
		return false;
	}
}


CQuad::CQuad(Vector& p, Vector& l1, Vector& l2):CPlane(p, (l1%l2)) {
	P=p;
	L1=l1;
	L2=l2;
}

CQuad::~CQuad() {
}

void CQuad::Draw(void) {
}
