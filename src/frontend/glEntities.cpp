/*
 * glEntities.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#include "glEntities.h"


GLEntities::GLEntities() {
	Bird *bird = new Bird(new Vector<float>(0.0, 0.0, 0.0),
			new Vector<float>(0.00f, 0.14f, 0.02f),
			new Color(0.0, 0.0, 1.0));

	boids = new Boids();
	boids->addBoid(bird);
}

GLEntities::~GLEntities() {
}


Boids *GLEntities::getBoids() {
	return boids;
}

/**
 * draw functions
 */

void GLEntities::drawBird() {

	double size = 0.02f;
	double bsize = size*7;
	double tsize = size;
	double wsize = bsize+0.1*bsize;
	double wlevel = 0;


	glPushMatrix();
	glBegin(GL_TRIANGLES);

		// heard
		glColor3f(0.0, 1.0, 0.0);
		glVertex3f( 0.0f, size, 0.0f);
		glVertex3f(-size,-size, size);
		glVertex3f( size,-size, size);

		glColor3f(1.0, 1.0, 0.0);
		glVertex3f( 0.0f, size, 0.0f);
		glVertex3f(size,-size, size);
		glVertex3f( size,-size, -size);

		glColor3f(0.0, 1.0, 1.0);
		glVertex3f( 0.0f, size, 0.0f);
		glVertex3f(size,-size, -size);
		glVertex3f(-size,-size, -size);

		glColor3f(0.0, 0.5, 0.0);
		glVertex3f( 0.0f, size, 0.0f);
		glVertex3f(-size,-size, -size);
		glVertex3f(-size,-size, size);

		// body
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f(-size,-size, size);
		glVertex3f( size,-size, size);

		glColor3f(0.0, 1.0, 0.0);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f(-size,-size, size);
		glVertex3f( size,-size, size);

		glColor3f(1.0, 1.0, 0.0);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f(size,-size, size);
		glVertex3f( size,-size, -size);

		glColor3f(0.0, 1.0, 1.0);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f(size,-size, -size);
		glVertex3f(-size,-size, -size);

		glColor3f(0.0, 0.5, 0.0);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f(-size,-size, -size);
		glVertex3f(-size,-size, size);

		// wings
		glColor3f(0.0, 0.0, 1.0);

		glVertex3f(wsize, -bsize/2, wlevel);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f( size,-size, size);

		glVertex3f(wsize, -bsize/2, wlevel);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f( size,-size, size/2);

		glVertex3f(wsize, -bsize/2, wlevel);
		glVertex3f( size,-size, size);
		glVertex3f( size,-size, size/2);

		glVertex3f(-wsize, -bsize/2, wlevel);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f(-size,-size, size);

		glVertex3f(-wsize, -bsize/2, wlevel);
		glVertex3f( 0.0f, -bsize, 0.0f);
		glVertex3f(-size,-size, size/2);

		glVertex3f(-wsize, -bsize/2, wlevel);
		glVertex3f(-size,-size, size);
		glVertex3f(-size,-size, size/2);

	glEnd();

	// tail
	glTranslatef(0.0f,-bsize-size, 0.0f);
	glBegin(GL_TRIANGLES);
		glColor3f(1.0, 0.0, 0.0);
		glVertex3f( 0.0f, tsize, 0.0f);
		glVertex3f(-tsize,0.0, tsize/2);
		glVertex3f( tsize,0.0, tsize/2);
	glEnd();

	glPopMatrix();
}
