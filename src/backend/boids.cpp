/*
 * Boids.cpp
 *
 *  Created on: Nov 8, 2010
 *      Author: lucmir
 */

#include "boids.h"

Boids::Boids() {
	boids = new std::vector<Bird *>();
}

Boids::~Boids() {
	boids->clear();
	delete(boids);
}

void Boids::addBoid(Bird *bird) {
	boids->push_back(bird);
}

