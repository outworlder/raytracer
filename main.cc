#include <GL/glut.h>

#include "mathclass.hpp"
#include "tracer.hpp"
#include "phong.hpp"
#include "GLScreen.hpp"
#include "sphere.hpp"
#include "plane.hpp"
#include "quad.hpp"
#include "GLPreview.hpp"

int width=700;
int height=700;

bool previewing=true;
bool complete=false;

float rotationx=0.0f;
float rotationy=0.0f;
float rotationz=0.0f;

float translation=-6.0f;

Vector eye(0.0f,0.0f,-1.0f);
CViewpoint viewpoint(eye);
CColor background(0.1f,0.1f,0.1f);
CScene scene(background,viewpoint);
GLScreen screen(width,height);
CColor ambient(0.2f,0.2f,0.2f);
Phong phong(ambient, 0.5f);
CRaytracer tracer(scene, screen, phong);

Vector n(0.0f,-1.0f,0.0f);
Vector p(-2.0f,1.0f,3.0f);
//Vector v1(1.0f,1.0f,1.0f);
//Vector v2(0.0f,-1.0f,-1.0f);
Vector v1(1.0f,0.0f,0.0f);
Vector v2(0.0f,1.0f,0.0f);
CQuad plane(p,v1,v2);

//CPlane plane(p,n);

Vector center(-0.5f,0.0f,1.5f);
CSphere sphere(center, 0.2f);

Vector center2(0.5f,-0.5f,1.5f);
CSphere sphere2(center2, 0.3f);

Vector center3(0.5f,0.5f,1.5f);
CSphere sphere3(center3, 0.3f);

Vector lpos(2.0f,1.0f,0.0f);
CColor lcolor(1.0f,1.0f,1.0f);
CLight light(lpos,lcolor, 0.5f);

void DrawScene(void);
void Test(void);
void SetupOrtho(void);
void SetupPerspective(void);
void KeyboardFunc(unsigned char key, int x, int y);
void InitGL(void);

void DrawScene(void) {
	glClearColor(0.0f,0.0f,0.0f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);	
	glLoadIdentity();
	if (complete || !previewing) {
		SetupOrtho();
		screen.Draw();
	} else {
		SetupPerspective();
		GLPreview::GetPreview().Draw();
	}
}

void Test(void) {
	glClearColor(0.5f,0.5f,0.5f,1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	
	glLoadIdentity();
	glColor3f(1.0f,0.0f,0.0f);
	glBegin(GL_TRIANGLES);
	glVertex3i(20,20,0);
	glVertex3i(50,40,0);
	glVertex3i(100,100,0);
	glEnd();
	glutSwapBuffers();
}
	
void SetupOrtho(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glOrtho(0.0f,width,height,0.0f,-5.0f,5.0f);	
	glMatrixMode(GL_MODELVIEW);
}

void SetupPerspective(void) {
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	if (width>height) {
		gluPerspective(45.0f,width/height,0.1f,20.0f);
	} else {
		gluPerspective(45.0f,height/width,0.1f,20.0f);
	}
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.0f,0.0f,translation);
	glRotatef(rotationx, 1.0f, 0.0f, 0.0f);
	glRotatef(rotationy, 0.0f, 1.0f, 0.0f);
	glRotatef(rotationz, 0.0f, 0.0f, 1.0f);
}

void KeyboardFunc(unsigned char key, int x, int y) {
	if (key=='r') {
		complete=false;
		if (previewing) {
			screen.Enabled(false);
			GLPreview::GetPreview().Enabled(true);
			SetupPerspective();
			tracer.Render(5);
			complete=true;
			DrawScene();
		} else {
			screen.Enabled(false);
			GLPreview::GetPreview().Enabled(false);
			SetupOrtho();
			tracer.Render(5);
			complete=true;
			DrawScene();
		}
	}
	
	if (key=='p') {
		complete=false;
		previewing=!previewing;
		DrawScene();
	}

	if (key=='q') exit(0);
	if (key=='t') Test();
	if (key=='d') DrawScene();

	if (key=='+') {
		translation-=1.0f;
		DrawScene();
	}
	
	if (key=='-') {
		translation+=1.0f;
		DrawScene();
	}

	if (key=='7') {
		rotationx-=1.0f;
		DrawScene();
	}
	
	if (key=='8') {
		rotationx+=1.0f;
		DrawScene();
	}

	if (key=='4') {
		rotationy+=1.0f;
		DrawScene();
	}

	if (key=='5') {
		rotationy-=1.0f;
		DrawScene();
	}

	if (key=='1') {
		rotationz+=1.0f;
		DrawScene();
	}

	if (key=='2') {
		rotationz-=1.0f;
		DrawScene();
	}
}

void InitGL(void) {
	glClearColor(0.0f,0.0f,0.0f,0.0f);
	glClearDepth(1.0f);
	glMatrixMode(GL_PROJECTION);
	//glColor3f(1.0f,1.0f,1.0f);
	glLoadIdentity();
	glViewport(0,0,width,height);	
	//glOrtho(0.0f,width,height,0.0f,-5.0f,5.0f);	
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
}

void Resize(int x, int y) {
	width=x;
	height=y;
	screen.Resize(x,y);
	complete=false;
	glViewport(0,0,width,height);
}

int main(int argc, char** argv) {
	phong.AddLight(light);
	CColor spherecolor(1.0f,0.0f,0.0f);
	sphere.Color(spherecolor);
	sphere.Shininess(0.001f);
	CColor spherecolor2(0.0f,1.0f,0.0f);
	sphere2.Color(spherecolor2);
	//CColor spherecolor3(0.0f,0.0f,0.0f);
	//sphere3.Color(spherecolor3);
	scene.AddObject(sphere2);
	sphere3.Diffuse(0.5f);
	sphere3.Specular(0.0f);
	sphere3.Reflectivity(0.0f);
	sphere3.Transparency(1.2f);
	scene.AddObject(sphere3);
	scene.AddObject(sphere);
	//plane.Diffuse(0.0f);
	//plane.Specular(0.0f);
	//plane.Reflectivity(0.5f);
	plane.Color(spherecolor);
	scene.AddObject(plane);

	glutInit(&argc, argv);
	glutInitWindowSize(width,height);
	glutInitWindowPosition(30,30);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGBA | GLUT_DEPTH);

	glutCreateWindow("Raytracer");

	InitGL();
	
	glutDisplayFunc(DrawScene);
	glutKeyboardFunc(KeyboardFunc);
	//glutIdleFunc(RefreshingFunc);
	glutReshapeFunc(Resize);
	glutMainLoop();
}													
