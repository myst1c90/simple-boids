/*
 * glEntities.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#include "glEntities.h"


GLEntities::GLEntities() {
	Bird *mainBird = new Bird(new Vector<float>(0.0, -1.0, 6.0),
			new Vector<float>(0.00f, 0.5f, 0.0f),
			new Color(0.3, 0.5, 0.0));
	boids = new Boids();
	boids->addBoid(mainBird);
	boids->getCenterPos()->set(mainBird->getPos()->getX(),
			mainBird->getPos()->getY(), mainBird->getPos()->getZ());

	camera = new Camera(0.0, 2.0, 5.0, 0.0, 0.0, -4.0, 0.0, 0.0, -1.0);
	tower = new Entity(0.0f,-0.2f,0.0f, 0.8, 5.0, 50, 0.4, 0.4, 0.4);
}

GLEntities::~GLEntities() {
}


Boids *GLEntities::getBoids() {
	return boids;
}

Bird *GLEntities::getMainBird() {
	return (*boids->getBoids())[0];
}

Camera *GLEntities::getCamera() {
	return camera;
}

Entity *GLEntities::getTower() {
	return tower;
}

void GLEntities::addBoid() {
	float x, y, z;

	Bird *mainBoid = (*boids->getBoids())[0];

	Bird *newBoid = new Bird(new Vector<float>(0.0, 0.0, 0.0),
			new Vector<float>(0.00f, 0.5f, 0.0f),
			new Color(1.0, 0.0, 0.0));

	do {
		srand( time(NULL) );
		x = (rand() % MAX_BOID_DIST)/10.0 + ( (rand() % 1000) / 10000.0 );
		x *= rand() % 2 ? -1 : 1;
		y = (rand() % MAX_BOID_DIST)/10.0 + ( (rand() % 1000) / 10000.0 );
		y *= rand() % 2 ? -1 : 1;
		z = (rand() % MAX_BOID_DIST)/10.0 + ( (rand() % 1000) / 10000.0 );
		z *= rand() % 2 ? -1 : 1;

		newBoid->getPos()->set(x + mainBoid->getPos()->getX(), y + mainBoid->getPos()->getY(), z + mainBoid->getPos()->getZ());
	} while(!boids->addBoid(newBoid));

	printf("NEW BOID AT: (%f, %f, %f)\tTOTAL: %d\n", x, y, z, boids->getBoids()->size());
}

void GLEntities::removeBoid() {
	if(boids->getBoids()->size() > 1) {
		boids->removeLastBoid();
		printf("REMOVED BOID\t\t\t\t\tTOTAL: %d\n", boids->getBoids()->size());
	}
}

/**
 * draw functions
 */
void GLEntities::drawBird(Bird *bird) {
	float wingPos = bird->getWingPos();

	float radius = 0.028;

	glColor3f(bird->getColor()->getR(), bird->getColor()->getG(),
			bird->getColor()->getB());
	glutSolidSphere(radius, 100, 100);

	glBegin(GL_TRIANGLES);
		// beak
		glColor3f(1.0, 1.0, 0.0);

		glVertex3f( 0.0f, 0.0f, BIRD_BEAK_A );
		glVertex3f( BIRD_BEAK_B, BIRD_BEAK_B, 0.0f );
		glVertex3f( -BIRD_BEAK_B, BIRD_BEAK_B, 0.0f );

		glVertex3f( 0.0f, 0.0f, BIRD_BEAK_A );
		glVertex3f( BIRD_BEAK_B, -BIRD_BEAK_B, 0.0f );
		glVertex3f( -BIRD_BEAK_B, -BIRD_BEAK_B, 0.0f );

		glVertex3f( 0.0f, 0.0f, BIRD_BEAK_A );
		glVertex3f( BIRD_BEAK_B, BIRD_BEAK_B, 0.0f );
		glVertex3f( BIRD_BEAK_B,-BIRD_BEAK_B, 0.0f );

		glVertex3f( 0.0f, 0.0f, BIRD_BEAK_A );
		glVertex3f( -BIRD_BEAK_B, BIRD_BEAK_B, 0.0f );
		glVertex3f( -BIRD_BEAK_B, -BIRD_BEAK_B, 0.0f );

		// wings
		glVertex3f( BIRD_BEAK_A, wingPos, 0.0f );
		glVertex3f( 0.0f, BIRD_WING_A, BIRD_WING_B );
		glVertex3f( 0.0f, BIRD_WING_A, -BIRD_WING_B );

		glVertex3f( BIRD_BEAK_A, wingPos, 0.0f);
		glVertex3f( 0.0f, -BIRD_WING_A, BIRD_WING_B );
		glVertex3f( 0.0f, -BIRD_WING_A, -BIRD_WING_B );

		glVertex3f( BIRD_BEAK_A, wingPos, 0.0f );
		glVertex3f( 0.0f, BIRD_WING_A, BIRD_WING_B );
		glVertex3f( 0.0f, -BIRD_WING_A, BIRD_WING_B );

		glVertex3f( BIRD_BEAK_A, wingPos, 0.0f );
		glVertex3f( 0.0f, BIRD_WING_A, -BIRD_WING_B );
		glVertex3f( 0.0f, -BIRD_WING_A, -BIRD_WING_B );

		glVertex3f( -BIRD_BEAK_A, wingPos, 0.0f);
		glVertex3f( 0.0f, BIRD_WING_A, BIRD_WING_B );
		glVertex3f( 0.0f, BIRD_WING_A, -BIRD_WING_B );

		glVertex3f( -BIRD_BEAK_A, wingPos, 0.0f );
		glVertex3f( 0.0f, -BIRD_WING_A, BIRD_WING_B );
		glVertex3f( 0.0f, -BIRD_WING_A,  -BIRD_WING_B );

		glVertex3f( -BIRD_BEAK_A, wingPos, 0.0f );
		glVertex3f( 0.0f, BIRD_WING_A, BIRD_WING_B );
		glVertex3f( 0.0f, -BIRD_WING_A, BIRD_WING_B );

		glVertex3f( -BIRD_BEAK_A, wingPos,0.0f);
		glVertex3f( 0.0f, BIRD_WING_A, -BIRD_WING_B );
		glVertex3f( 0.0f, -BIRD_WING_A, -BIRD_WING_B );

	glEnd();

	// eyes
/*	glColor3f(1.0, 1.0, 1.0);
	glTranslatef(0.01f, 0.02f, -BIRD_EYE);
	glutSolidSphere(0.008, 100, 100);
	glTranslatef(-0.02f, 0.00f, 0);
	glutSolidSphere(0.008, 100, 100);
	glColor3f(0.0, 0.0, 0.0);
	glTranslatef(0.00f, 0.00f, -0.004);
	glutSolidSphere(0.005, 100, 100);
	glTranslatef(0.02f, 0.00f, 0.0);
	glutSolidSphere(0.005, 100, 100);
*/
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

