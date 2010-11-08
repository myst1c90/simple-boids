/*
 * Bird.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#include "bird.h"

Bird::Bird(Vector<float> *initPos, Vector<float> *vol, Color *color) :
	Entity(initPos, vol, color) {
	this->vel = new Vector<float>();
}

Bird::Bird(float posX, float posY, float posZ, float volX, float volY,
		float volZ, float colorR, float colorG, float colorB) :
		Entity(posX, posY, posZ, volX, volY, volZ, colorR, colorG, colorB) {
	this->vel = new Vector<float>();
}

Bird::~Bird() {
	this->~Entity();
	delete(vel);
}

Vector<float> *Bird::getVel() {
	return vel;
}

