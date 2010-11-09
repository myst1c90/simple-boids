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

	qx.s = 1.0f; qx.vx = 1.0f; qx.vy = 0.0f; qx.vz = 0.0f;
	qy.s = 1.0f; qy.vx = 0.0f; qy.vy = 1.0f; qy.vz = 0.0f;
	qz.s = 1.0f; qz.vx = 0.0f; qz.vy = 0.0f; qz.vz = 1.0f;
	updateMatrix();
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

void Bird::updateMatrix() {
	matrix[0] = qx.vx;
	matrix[1] = qx.vy;
	matrix[2] = qx.vz;
	matrix[3] = 0;

	matrix[4] = qy.vx;
	matrix[5] = qy.vy;
	matrix[6] = qy.vz;
	matrix[7] = 0;

	matrix[8] = qz.vx;
	matrix[9] = qz.vy;
	matrix[10] = qz.vz;
	matrix[11] = 0;

	matrix[12] = 0;
	matrix[13] = 0;
	matrix[14] = 0;
	matrix[15] = 1;
}

void Bird::xRotate() {
	quat_rot_t rot;
	rot.theta = 20;
	rot.nx = 1;
	rot.ny = 0;
	rot.nz = 1;
	quat_pos_t p = quatRotate(quatToPosition(qx), rot);
	qx = quatFromPosition(p);
}

void Bird::yRotate() {
	quat_rot_t rot;
	rot.theta = 20;
	rot.nx = 1;
	rot.ny = 0;
	rot.nz = 0;
	quat_pos_t p = quatRotate(quatToPosition(qy), rot);
	qy = quatFromPosition(p);
}

float *Bird::getMatrix() {
	return matrix;
}

