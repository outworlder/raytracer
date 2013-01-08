#include "GLScreen.hpp"
#include <iostream>
#include <assert.h>

//#define GLSCREEN_DEBUG 1

void GLScreen::PutPixel(int x, int y, CColor& color) {
	static int counter=0;
	if (needsresizing) Recreate();
	assert(x<tx  && y<ty);
	
	framebuffer[x][y]=color;
	
	if (enabled) {
		counter++;
		if (counter >= tx) {
			counter=0;
			Draw();
		}
	}
#ifdef GLSCREEN_DEBUG
	std::cerr << "PutPixel: " << x << " " << y << '\n';
	std::cerr << "Cor: R=" << color.R << " G=" << color.G << " B=" << color.B << "\n";
#endif
}

void GLScreen::Clear(void) {
	for (int loop=0; loop < tx; loop++) {
		delete[] framebuffer[loop];
	}
	delete[] framebuffer;
	framebuffer=new CColor*[tx];
	for (int loop=0; loop < tx; loop++) {
		framebuffer[loop]=new CColor[ty];
	}

}

void GLScreen::Draw(void) {
	CColor temp;
	glBegin(GL_POINTS);
	for (int loopy=0; loopy<ty; loopy++)
		for (int loopx=0; loopx<tx; loopx++) {
			temp=framebuffer[loopx][loopy];
			glColor3f(temp.R,temp.G,temp.B);
			glVertex2i(loopx,loopy);
		}
	glEnd();
	glutSwapBuffers();
}

GLScreen::GLScreen(int x, int y):CScreen(x,y) {
	needsresizing=false;
	framebuffer=new CColor*[x];
	for (int loop=0; loop < x; loop++) {
		framebuffer[loop]=new CColor[y];
	}
}

GLScreen::~GLScreen(void) {
	for (int loop=0; loop < tx; loop++) {
		delete[] framebuffer[loop];
	}
	delete[] framebuffer;
}

void GLScreen::Enabled(bool state) {
	enabled=state;
}

void GLScreen::Resize(int x, int y) {
	newtx=x;
	newty=y;
	needsresizing=true;
}

void GLScreen::Recreate(void) {
	for (int loop=0; loop < tx; loop++) {
		delete[] framebuffer[loop];
	}
	delete[] framebuffer;
	needsresizing=false;
	tx=newtx;
	ty=newty;

	framebuffer=new CColor*[newtx];
	for (int loop=0; loop < newtx; loop++) {
		framebuffer[loop]=new CColor[newty];
	}
}
