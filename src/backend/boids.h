/*
 * Boids.h
 *
 *  Created on: Nov 8, 2010
 *      Author: lucmir
 */

#ifndef BOIDS_H_
#define BOIDS_H_

#include <iostream>
#include <vector>

#include "bird.h"


class Boids {

	std::vector<Bird *> *boids;

	public:

		Boids();
		virtual ~Boids();

		void addBoid(Bird *bird);
};

#endif /* BOIDS_H_ */

