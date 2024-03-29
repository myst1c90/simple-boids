/*
 * Bird.h
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#ifndef BIRD_H_
#define BIRD_H_

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#include "entity.h"
#include "quaternion.h"

#define		DEGREESX_DEFAULT_VALUE		0.0
#define		DEGREESY_DEFAULT_VALUE		0.0
#define		MAX_DEGREESX				5.0
#define		MAX_DEGREESY				5.0
#define		MAX_VELOCITY				0.05
#define		MIN_VELOCITY				0.0
#define		MAX_WING_POS				0.02
#define		WING_VEL					0.002


class Bird : public Entity {

	float vel;				// velocity
	Vector<float> *dir;		// direction vector

	float matrix[16];		// transformation matrix
	Quaternion *qX;
	Quaternion *qY;
	float degreesX;
	float degreesY;

	float wingPos;
	bool wingDir;


	public:

		Bird(Vector<float> *initPos, Vector<float> *vol, Color *color);
		Bird(float posX, float posY, float posZ, float volX, float volY,
			float volZ, float colorR, float colorG, float colorB);
		virtual ~Bird();

		void updateMatrix();
		void updatePosition();
		void updateWingPos();
		void updateVelocity(float vel);
		void rotateX(float degrees);
		void rotateY(float degrees);

		float *getMatrix();
		Vector<float> *getDir();
		float getDegreesX();
		float getDegreesY();
		float getWingPos();
		void setVel(float vel);

};

#endif /* BIRD_H_ */
