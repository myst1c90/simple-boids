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


#define		BIRD_RADIUS		0.025
#define		BIRD_BEAK_A		-0.050
#define		BIRD_BEAK_B		0.018
#define		BIRD_WING_A		0.009333
#define		BIRD_WING_B		0.025454
#define		BIRD_EYE		0.023


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
