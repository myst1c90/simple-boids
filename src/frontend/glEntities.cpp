/*
 * glEntities.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#include "glEntities.h"


GLEntities::GLEntities() {
	mainBird = new Bird(new Vector<float>(0.0, -1.0, 1.0),
			new Vector<float>(0.00f, 0.5f, 0.0f),
			new Color(0.3, 0.5, 0.0));


	camera = new Camera(0.0, 1.0, 5.0, 0.0, 0.0, -4.0, 0.0, 0.0, -1.0);

	boids = new Boids();

	Bird *bird2 = new Bird(new Vector<float>(0.0, -0.3, 1.0),
				new Vector<float>(0.00f, 0.5f, 0.0f),
				new Color(1.0, 0.0, 0.0));
	boids->addBoid(bird2);

	tower = new Entity(0.0f,-0.2f,0.0f, 0.6, 1.8, 50, 0.4, 0.4, 0.4);
}

GLEntities::~GLEntities() {
}


Boids *GLEntities::getBoids() {
	return boids;
}

Bird *GLEntities::getMainBird() {
	return mainBird;
}

Camera *GLEntities::getCamera() {
	return camera;
}

Entity *GLEntities::getTower() {
	return tower;
}

/**
 * draw functions
 */

void GLEntities::drawBird(Bird *bird) {
	float wingPos = bird->getWingPos();

	float radius = 0.05;

	glColor3f(bird->getColor()->getR(), bird->getColor()->getG(),
			bird->getColor()->getB());
	glutSolidSphere(radius, 100, 100);

	glColor3f(1.7, 1.7, 0.0);
	glBegin(GL_TRIANGLES);
		// beak
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

		// wings
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

	// eyes
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
}

void GLEntities::drawTower() {
	glPushMatrix();

	glColor3f(tower->getColor()->getR(), tower->getColor()->getG(),
			tower->getColor()->getB());
	glTranslatef(tower->getPos()->getX(), tower->getPos()->getY(), tower->getPos()->getZ());
	glRotatef(270, 1.0, 0.0, 0.0);
	glutWireCone(tower->getVol()->getX(), tower->getVol()->getY(),
			tower->getVol()->getZ(), tower->getVol()->getZ());

	glPopMatrix();
}
