/*
 * Bird.h
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#ifndef BIRD_H_
#define BIRD_H_

#include "entity.h"
#include "quat/quat.h"


class Bird : public Entity {

	Vector<float> *vel;		// velocity

	float matrix[16];
	quat_t qx;
	quat_t qy;
	quat_t qz;



	public:

		Bird(Vector<float> *initPos, Vector<float> *vol, Color *color);
		Bird(float posX, float posY, float posZ, float volX, float volY,
			float volZ, float colorR, float colorG, float colorB);
		virtual ~Bird();

		Vector<float> *getVel();

		void updateMatrix();
		void xRotate();
		void yRotate();
		float *getMatrix();

};

#endif /* BIRD_H_ */
