/*
 * glEntities.h
 *
 *  Created on: Nov 7, 2010
 *      Author: lucmir
 */

#ifndef GLENTITIES_H_
#define GLENTITIES_H_

#include <GL/glut.h>
#include <iostream>
#include <vector>

#include "../backend/boids.h"


class GLEntities {

	Boids *boids;

	Entity *tower;

	//TODO terrain

	public:

		GLEntities();
		virtual ~GLEntities();

		// draw functions
		void drawBird();

		Boids *getBoids();
};

#endif /* GLENTITIES_H_ */
