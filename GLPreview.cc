#include "GLPreview.hpp"

void GLPreview::AddRay(CRay& ray) {
	rays.push_back(&ray);
	if (enabled) Draw();
}

void GLPreview::AddObject(CObject& object) {
	objects.push_back(&object);
	if (enabled) Draw();
}

void GLPreview::AddLight(CLight& light) {
	lights.push_back(&light);
	if (enabled) Draw();
}

void GLPreview::RemoveRay(CRay& ray) {
	std::vector<CRay*>::iterator loop;

	loop=rays.begin();

	do {
		if ((*loop)==&ray) {
			rays.erase(loop);
			break;
		}
		loop++;
	} while (loop!=rays.end());
}

void GLPreview::RemoveObject(CObject& object) {
	std::vector<CObject*>::iterator loop;

	loop=objects.begin();

	do {
		if ((*loop)==&object) {
			objects.erase(loop);
			break;
		}
		loop++;
	} while (loop!=objects.end());
}

void GLPreview::Draw(void) {
	std::vector<CObject*>::iterator obloop;
	std::vector<CRay*>::iterator rayloop;
	std::vector<CLight*>::iterator lightloop;

	obloop=objects.begin();
	rayloop=rays.begin();
	lightloop=lights.begin();

	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	while (lightloop!=lights.end()) {
		if (*lightloop) {
			(*lightloop)->Draw();
		}
		lightloop++;
	}
	
	while (obloop!=objects.end()) {
		if (*obloop) {
			(*obloop)->Draw();
		}
		obloop++;
	}

	while (rayloop!=rays.end()) {
		if (*rayloop) {
			DrawRay(*(*rayloop));
		}
		rayloop++;
	}

	glutSwapBuffers();
}


void GLPreview::DrawRay(CRay& ray) {
	glColor3f(1.0f,1.0f,1.0f);
	glBegin(GL_LINES);
	glVertex3f(ray.Origin().Position().x, ray.Origin().Position().y, ray.Origin().Position().z);
	glVertex3f(ray.AtPos(5).Position().x, ray.AtPos(5).Position().y, ray.AtPos(5).Position().z);
	glEnd();
}

GLPreview& GLPreview::GetPreview(void) {
	static GLPreview Preview;
	return Preview;
}

void GLPreview::Enabled(bool state) {
	enabled=state;
}

GLPreview::GLPreview() {
	enabled=false;
}


