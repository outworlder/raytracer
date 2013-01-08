#ifndef PHONG_HPP
#define PHONG_HPP

#include "mathclass.hpp"
#include "tracer.hpp"

class Phong : public CShader {
public:
	virtual CColor Shade(SiData& d, Vector& v, CScene* scene);
	virtual CColor Combine(SiData& d, CColor& local, CColor& reflected, CColor& transmitted);
	Phong(CColor& amb, float inten);
};

#endif
