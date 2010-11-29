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

#define		COHESION_COEFF		120
#define		SEPARATION_COEFF	0.15
#define		ALIGNMENT_COEFF		70
#define		MIN_DISTANCE		SEPARATION_COEFF
#define		OBSTACLE_AVOID_COEFF		30
#define		MIN_SPACE			0.01

class Boids {

	std::vector<Bird *> *boids;

	public:

		Boids();
		virtual ~Boids();

		bool addBoid(Bird *bird);
		void removeLastBoid();
		std::vector<Bird *> *getBoids();

		void updateBoidsPosition(Entity *obstacle);
		Vector<float> rule1(int boidNum);
		Vector<float> rule2(int boidNum);
		Vector<float> rule3(int boidNum);
		Vector<float> avoidObstacle(int boidNum, Entity *obstacle);
};

#endif /* BOIDS_H_ */

