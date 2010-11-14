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
#include "../backend/camera.h"


class GLEntities {

	Boids *boids;		// boids (group of birds)
	Bird *mainBird;		// main (objective) bird

	Camera *camera;		// view camera
	Entity *tower;		// tower


	public:

		GLEntities();
		virtual ~GLEntities();

		// draw functions
		void drawBird(Bird *bird);
		void drawTower();

		Boids *getBoids();
		Bird *getMainBird();
		Camera *getCamera();

};

#endif /* GLENTITIES_H_ */
