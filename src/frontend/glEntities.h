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


#define 	MAX_BOID_DIST	5


class GLEntities {

	Boids *boids;		// boids (set of birds)

	Camera *camera;		// view camera
	Entity *tower;		// tower


	public:

		GLEntities();
		virtual ~GLEntities();

		// draw functions
		void drawBird(Bird *bird);
		void drawTower();

		void addBoid();
		void removeBoid();

		Boids *getBoids();
		Bird *getMainBird();
		Camera *getCamera();
		Entity *getTower();

};

#endif /* GLENTITIES_H_ */
