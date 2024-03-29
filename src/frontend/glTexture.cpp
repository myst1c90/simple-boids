
#include "glTexture.h"

GLTexture::GLTexture(const char *filename) {
	tex = SOIL_load_OGL_texture(
		filename,
		SOIL_LOAD_RGBA,
		SOIL_CREATE_NEW_ID,
		SOIL_FLAG_MULTIPLY_ALPHA
	);

	if(!tex) {
		throw std::runtime_error("Can\'t load texture!\n");
	}
}

GLTexture::GLTexture(const char *filename, long size, long bWidth, long bHeight) {
	FILE *image;
	char *data = (char*) malloc(size);
	bWidth = 512;
	bHeight = 512;

	image = fopen(filename, "rb");
	fread(data, size, 1, image);
	glGenTextures(1, &tex);
	glBindTexture(GL_TEXTURE_2D, tex);

	gluBuild2DMipmaps(GL_TEXTURE_2D, 0, bWidth, bHeight, GL_RGBA, GL_UNSIGNED_BYTE, data);
}



void GLTexture::drawEntire(double x_orig,double y_orig,
	double x_dest,double y_dest) {
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
		glTexCoord3f (0.0f, 0.0f, -6.5f); glVertex3f (x_orig,y_orig, -6.5f);
		glTexCoord3f (1.0f, 0.0f, -6.5f); glVertex3f (x_dest,y_orig, -6.5f);
		glTexCoord3f (1.0f, 1.0f, -6.5f); glVertex3f (x_dest,y_dest, -6.5f);
		glTexCoord3f (0.0f, 1.0f, -6.5f); glVertex3f (x_orig,y_dest, -6.5f);
	glEnd();
}

void GLTexture::drawEntireReverseX(double x_orig,double y_orig,
	double x_dest,double y_dest) {
	glBindTexture(GL_TEXTURE_2D,tex);
	glBegin(GL_QUADS);
		glTexCoord2f (0.0f, 0.0f); glVertex2f (x_dest,y_orig);
		glTexCoord2f (1.0f, 0.0f); glVertex2f (x_orig,y_orig);
		glTexCoord2f (1.0f, 1.0f); glVertex2f (x_orig,y_dest);
		glTexCoord2f (0.0f, 1.0f); glVertex2f (x_dest,y_dest);
	glEnd();
}



GLuint GLTexture::getTex() {
	return tex;
}



