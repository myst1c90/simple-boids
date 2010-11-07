#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "soil/SOIL.h"
#include "GL/glut.h"
#include <stdexcept>

class GLTexture
{
	public:

		GLuint tex;

	public:

		GLTexture(const char *filename);
		void drawEntire(double x_orig,double y_orig,double x_dest,double y_dest);
		void drawEntireReverseX(double x_orig,double y_orig,double x_dest,double y_dest);
		GLuint getTex();
};

#endif
