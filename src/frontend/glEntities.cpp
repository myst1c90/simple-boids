/*
 * glEntities.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#include "glEntities.h"


GLEntities::GLEntities() {
	Bird *bird = new Bird(new Vector<float>(0.0, -0.5, 0.5),
			new Vector<float>(0.00f, 0.5f, 0.0f),
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

void GLEntities::drawBird(float wingPos) {

	double size = 0.02f;
	double bsize = size*7;

	float radius = 0.05;

	glColor3f(0.3, 0.7, 0.0);
	glutSolidSphere(radius, 100, 100);

	glColor3f(1.7, 1.7, 0.0);
	glBegin(GL_TRIANGLES);
		// bico
		glVertex3f( 0.0f, 0.0f, -(radius+0.03));
		glVertex3f(radius/1.5,radius/1.5, 0.0f);
		glVertex3f( -radius/1.5,radius/1.5, 0.0f);

		glVertex3f( 0.0f, 0.0f, -(radius+0.03));
		glVertex3f(radius/1.5,-radius/1.5, 0.0f);
		glVertex3f( -radius/1.5,-radius/1.5, 0.0f);

		glVertex3f( 0.0f, 0.0f, -(radius+0.03));
		glVertex3f(radius/1.5,radius/1.5, 0.0f);
		glVertex3f(radius/1.5,-radius/1.5, 0.0f);

		glVertex3f( 0.0f, 0.0f, -(radius+0.03));
		glVertex3f( -radius/1.5,radius/1.5, 0.0f);
		glVertex3f( -radius/1.5,-radius/1.5, 0.0f);

		// asa
		glVertex3f( -(radius+0.03), wingPos, 0.0f);
		glVertex3f(0.0f,radius/3, radius/1.1);
		glVertex3f(0.0f,radius/3, -radius/1.1);

		glVertex3f( -(radius+0.03), wingPos, 0.0f);
		glVertex3f(0.0f, -radius/3, radius/1.1);
		glVertex3f(0.0f,-radius/3,  -radius/1.1);

		glVertex3f( -(radius+0.03), wingPos, 0.0f);
		glVertex3f(0.0f,radius/3, radius/1.1);
		glVertex3f(0.0f, -radius/3, radius/1.1);

		glVertex3f( -(radius+0.03), wingPos,0.0f);
		glVertex3f( 0.0f,radius/3, -radius/1.1);
		glVertex3f( 0.0f,-radius/3, -radius/1.1);

		glVertex3f( (radius+0.03), wingPos, 0.0f);
		glVertex3f(0.0f,radius/3, radius/1.1);
		glVertex3f(0.0f,radius/3, -radius/1.1);

		glVertex3f( (radius+0.03), wingPos, 0.0f);
		glVertex3f(0.0f, -radius/3, radius/1.1);
		glVertex3f(0.0f,-radius/3,  -radius/1.1);

		glVertex3f( (radius+0.03), wingPos, 0.0f);
		glVertex3f(0.0f,radius/3, radius/1.1);
		glVertex3f(0.0f, -radius/3, radius/1.1);

		glVertex3f( (radius+0.03), wingPos,0.0f);
		glVertex3f( 0.0f,radius/3, -radius/1.1);
		glVertex3f( 0.0f,-radius/3, -radius/1.1);

	glEnd();

	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.013f, 0.02f, -radius+0.005);
	glutSolidSphere(0.008, 100, 100);
	glTranslatef(-0.026f, 0.00f, 0);
	glutSolidSphere(0.008, 100, 100);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.00f, 0.00f, -0.004);
	glutSolidSphere(0.005, 100, 100);
	glTranslatef(0.026f, 0.00f, 0.0);
	glutSolidSphere(0.005, 100, 100);

	glPopMatrix();
}


