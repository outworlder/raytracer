#ifndef GLSCREEN_HPP
#define GLSCREEN_HPP

#include <GL/glut.h>

#include "tracer.hpp"

class GLScreen : public CScreen {
 protected:
	 bool needsresizing;
	 bool enabled;
	 CColor** framebuffer;
	 void Recreate(void);
 public:	 
	virtual void PutPixel(int x, int y, CColor& color);
	virtual void Clear(void);
	virtual void Draw(void);
	virtual void Resize(int x, int y);

	void Enabled(bool state);

	GLScreen(int x, int y);
	virtual ~GLScreen(void);
};

#endif
