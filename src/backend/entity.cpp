/*
 * Entity.cpp
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#include "entity.h"

Entity::Entity(Vector<float> *initPos, Vector<float> *vol, Color *color) {
	this->pos = initPos;
	this->vol = vol;
	this->color = color;
}

Entity::Entity(float posX, float posY, float posZ, float volX, float volY,
		float volZ, float colorR, float colorG, float colorB) {
	this->pos = new Vector<float>(posX, posY, posZ);
	this->vol = new Vector<float>(volX, volY, volZ);
	this->color = new Color(colorR, colorG, colorB);
}

Entity::~Entity() {
	delete(pos);
	delete(vol);
	delete(color);
}

Vector<float> *Entity::getPos() {
	return pos;
}

Vector<float> *Entity::getVol() {
	return vol;
}

Color *Entity::getColor() {
	return color;
}
