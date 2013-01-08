#ifndef GLPREVIEW_HPP
#define GLPREVIEW_HPP

#include <GL/glut.h>
#include "tracer.hpp"

class CObject;
class CRay;
class CLight;

class GLPreview {
private:
	std::vector<CObject*> objects;
	std::vector<CRay*> rays;
	std::vector<CLight*> lights;
	bool enabled;
protected:
	void DrawRay(CRay& ray);
	GLPreview();
public:
	void AddRay(CRay& ray);
	void AddObject(CObject& object);
	void AddLight(CLight& light);
	void RemoveRay(CRay& ray);
	void RemoveObject(CObject& object);
	void Enabled(bool state);
	
	void Draw(void);
	
	static GLPreview& GetPreview(void);
};

#endif
