#ifndef GLTEXTURE_H
#define GLTEXTURE_H

#include "soil/SOIL.h"
#include "GL/glut.h"
#include <stdio.h>
#include <stdexcept>

class GLTexture
{
	public:

		GLuint tex;

	public:

		GLTexture(const char *filename);
		GLTexture(const char *filename, long size, long bWidth, long bHeight);
		void drawEntire(double x_orig,double y_orig,double x_dest,double y_dest);
		void drawEntireReverseX(double x_orig,double y_orig,double x_dest,double y_dest);
		GLuint getTex();
};

#endif
