/*
 * Bird.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#include "bird.h"

Bird::Bird(Vector<float> *initPos, Vector<float> *vol, Color *color) :
	Entity(initPos, vol, color) {
	dir = new Vector<float>();
	qX = new Quaternion();
	qY = new Quaternion();
	degreesX = DEGREESX_DEFAULT_VALUE;
	degreesY = DEGREESY_DEFAULT_VALUE;
	vel = 0;
}

Bird::Bird(float posX, float posY, float posZ, float volX, float volY,
		float volZ, float colorR, float colorG, float colorB) :
		Entity(posX, posY, posZ, volX, volY, volZ, colorR, colorG, colorB) {
	dir = new Vector<float>();
	qX = new Quaternion();
	qY = new Quaternion();
	degreesX = DEGREESX_DEFAULT_VALUE;
	degreesY = DEGREESY_DEFAULT_VALUE;
	vel = 0;
}

Bird::~Bird() {
	this->~Entity();
	delete(dir);
}

void Bird::updateMatrix() {
	Quaternion q;

	// generate the quaternions that will represent the rotations
	qX->createFromAxisAngle(1.0f, 0.0f, 0.0f, degreesX);
	qY->createFromAxisAngle(0.0f, 1.0f, 0.0f, degreesY);
	Quaternion qz;

	// combine the x and y rotations
	q = (*qX) * (*qY);
	q.createMatrix(matrix);
}

void Bird::updatePosition() {
	Quaternion q;

	// create a matrix from the x quaternion and get the j vector
	qX->createMatrix(matrix);
	dir->setY(matrix[9]);

	// combine the y and x rotations
	q = (*qY) * (*qX);
	q.createMatrix(matrix);

	// get the i and k vector
	dir->setX(matrix[8]);
	dir->setZ(-matrix[10]);

	// scale the direction by our speed.
	(*dir) *= vel;

	// increment position by the direction vector
	(*pos) += (*dir);

}

void Bird::rotateX(float degrees) {
	if(fabs(degrees) < fabs(MAX_DEGREESX)) {
		degreesX += degrees;
	}
	else {
		if(degrees < 0)	{
			degreesX -= MAX_DEGREESX;
		}
		else {
			degreesX += MAX_DEGREESX;
		}
	}

	if(degreesX > 360.0f) {
		degreesX -= 360.0f;
	}
	else if(degreesX < -360.0f) {
		degreesX += 360.0f;
	}
}

void Bird::rotateY(float degrees) {
	if(fabs(degrees) < fabs(MAX_DEGREESY)) {
		degreesY += degrees;
	}
	else {
		if(degrees < 0)	{
			degreesY -= MAX_DEGREESY;
		}
		else {
			degreesY += MAX_DEGREESY;
		}
	}

	if(degreesY > 360.0f) {
		degreesY -= 360.0f;
	}
	else if(degreesY < -360.0f) {
		degreesY += 360.0f;
	}
}

void Bird::updateVelocity(float vel) {
	this->vel += vel;

	if(this->vel > MAX_VELOCITY) {
		this->vel = MAX_VELOCITY;
	}
	else if(this->vel < MIN_VELOCITY) {
		this->vel = MIN_VELOCITY;
	}
}

float *Bird::getMatrix() {
	return matrix;
}

Vector<float> *Bird::getDir() {
	return dir;
}

float Bird::getDegreesX() {
	return degreesX;
}

float Bird::getDegreesY() {
	return degreesY;
}
