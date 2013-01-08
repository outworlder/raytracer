#include "phong.hpp"

//#define PHONG_DEBUG 1

CColor Phong::Shade(SiData& d, Vector& v, CScene* scene) {
	std::vector<CLight*>::iterator loop;

	if (lights.size()==0) return CColor(0.0f,0.0f,0.0f);
	
	CColor result;
	
	CColor Ia;

	//Ia=ambint*ambient;
	
	loop=lights.begin();

	while (loop!=lights.end()) {
#ifdef PHONG_DEBUG
		std::cerr << "Entrou no loop shade. \n";
#endif
		Vector light((*loop)->Position()-d.Position);
		light.Normalize();
		CRay shade(d.Position, light);
		SiData dummy;
		CColor Ambient(ambient*d.Object->Ambient()*d.Object->Color());
		if (!scene->HasIntersection(shade, dummy, true)) {

			float diffuse=(d.Normal*light);
		
			if (diffuse<0) {
				diffuse=0;
			}
		
			Vector Eye(v-d.Position);
			Eye.Normalize();
			Vector H(light+Eye);
			H.Normalize();

			float dot = (d.Normal*H);
			float specular;

			if (dot >0) {
				//specular=pow(dot,d.Object->Shininess());
				specular=pow(dot, 5.0f);
			} else {
				specular=0;
			}
		
			result=Ambient+d.Object->Diffuse()*diffuse*d.Object->Color()+(d.Object->Specular()*specular);
		}
		else {
			result=Ambient;
		}
		++loop;
	}
	
#ifdef PHONG_DEBUG
	std::cerr << "Phong::Shade R=" << result.R << " G=" << result.G << " B=" << result.B << "\n";
#endif
	
	return result;
}

CColor Phong::Combine(SiData& d, CColor& local, CColor& reflected, CColor& transmitted) {
	return CColor(local+reflected+transmitted);
}

Phong::Phong(CColor& amb, float inten) {
	ambient=amb;
	ambint=inten;
}
