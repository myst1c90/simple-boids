/*
 * Entity.h
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#ifndef ENTITY_H_
#define ENTITY_H_

#include "color.h"
#include "vector.h"


class Entity {

	Vector<float> *pos;		// position
	Vector<float> *vol;		// volume
	Color *color;			// RGB color

	public:

		Entity(Vector<float> *initPos, Vector<float> *vol, Color *color);
		Entity(float posX, float posY, float posZ, float volX, float volY,
			float volZ, float colorR, float colorG, float colorB);
		virtual ~Entity();

		Vector<float> *getPos();
		Vector<float> *getVol();
		Color *getColor();

};

#endif /* ENTITY_H_ */
