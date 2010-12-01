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

#define		MIN_SPACE			0.001
#define		BOIDS_VEL_COEFF		100
#define 	MAX_BOID_DIST		10

enum Coeff {
	COHESION_1,	COHESION_2, COHESION_3,	COHESION_4,	COHESION_5,
	SEPARATION_1, SEPARATION_2,	SEPARATION_3, SEPARATION_4, SEPARATION_5,
	ALIGMENT_1, ALIGMENT_2, ALIGMENT_3, ALIGMENT_4, ALIGMENT_5,
	OBSTACLE_AVOID_1, OBSTACLE_AVOID_2, OBSTACLE_AVOID_3, OBSTACLE_AVOID_4, OBSTACLE_AVOID_5,
};

class Boids {

	float cohesionCoeff;
	float separationCoeff;
	float aligmentCoeff;
	float obstacleAvoidCoeff;
	float minDistance;

	std::vector<Bird *> *boids;
	Vector<float> *centerPos;
	Vector<float> *centerDir;

	public:

		Boids();
		virtual ~Boids();

		bool addBoid(Bird *bird);
		void removeLastBoid();
		std::vector<Bird *> *getBoids();

		void updateBoidsPosition(Entity *obstacle);
		int updateCenter();
		Vector<float> rule1(int boidNum);
		Vector<float> rule2(int boidNum);
		Vector<float> rule3(int boidNum);
		Vector<float> avoidObstacle(int boidNum, Entity *obstacle);

		Vector<float> *getCenterPos();
		Vector<float> *getCenterDir();

		void setCohesionCoeff(float coeff);
		void setSeparationCoeff(float coeff);
		void setAligmentCoeff(float coeff);
		void setObstacleAvoidCoeff(float coeff);
};

#endif /* BOIDS_H_ */

