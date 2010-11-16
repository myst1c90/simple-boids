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

std::vector<Bird *> *Boids::getBoids() {
	return boids;
}

/*
 * Boids algorithms
 */
void Boids::updateBoidsPosition() {
	int numBoids = boids->size();
	Vector<float> newPosList1[numBoids];
	Vector<float> newPosList2[numBoids];
	Vector<float> newPosList3[numBoids];

	// compute new position for all the boids
	for(int i=1; i<numBoids; i++) {
		newPosList1[i] = rule1(i);
		newPosList2[i] = rule2(i);
		newPosList3[i] = rule3(i);
	}

	// apply the new positions
	for(int i=1; i<numBoids; i++) {
		Bird *b = (*boids)[i];
		Vector<float> *newPos1 = &newPosList1[i];
		Vector<float> *newPos2 = &newPosList2[i];
		Vector<float> *newPos3 = &newPosList3[i];

		*b->getDir() += *newPos1 + *newPos2 + *newPos3;
		*b->getPos() += *b->getDir();
		 b->setVel( (b->getDir())->magnitude()*10 );
	}
}


// rule 1: Cohesion - boids try to fly towards the centre of mass of neighbouring boids.
Vector<float> Boids::rule1(int boidNum) {
	int numNeighbours = 0;
	int numBoids = boids->size();
	Vector<float> center(0.0,0.0,0.0);
	Bird *b = (*boids)[boidNum];

	for(int i=0; i<numBoids; i++) {
		if(i!= boidNum)	{
			Bird *b_i = (*boids)[i];
			Vector<float> distVec = *b->getPos() - *b_i->getPos();
			float dist = distVec.magnitude();
		//	if(dist < MIN_DISTANCE) {
				center = center + (*b_i->getPos());
				numNeighbours++;
		//	}
		}
	}

	if(numNeighbours != 0) {
		center = center / numNeighbours;
		center = (center - *b->getPos()) / COHESION_COEFF;
		return center;
	}

	return Vector<float>(0.0, 0.0, 0.0);
}

// rule 2: Separation - boids try to keep a small distance away from other objects (including other boids).
Vector<float> Boids::rule2(int boidNum) {
	int numBoids = boids->size();
	Vector<float> disp(0.0,0.0,0.0);
	Bird *b = (*boids)[boidNum];

	for(int i=0; i<numBoids; i++) {
		if(i!= boidNum)	{
			Bird *b_i = (*boids)[i];
			Vector<float> distVec = *b->getPos() - *b_i->getPos();

			float dist = distVec.magnitude();

			if(dist < MIN_DISTANCE)	{
				Vector<float> unitVect = distVec / dist;
				disp = disp + unitVect * (SEPARATION_COEFF-dist);
			}
		}
	}

	return disp;
}


// rule 3: alignment - the boids try to match their velocity with their neighbours.
Vector<float> Boids::rule3(int boidNum) {
	int numNeighbours = 0;
	int numBoids = boids->size();
	Vector<float> totalVel(0.0,0.0,0.0);
	Bird *b = (*boids)[boidNum];

	for(int i=0; i<numBoids; i++) {
		if(i!= boidNum)	{
			Bird *b_i = (*boids)[i];
			Vector<float> distVec = b->getPos() - b_i->getPos();
			float dist = distVec.magnitude();

		//	if(dist <= MIN_DISTANCE) {
				totalVel = totalVel - *b_i->getDir();
				numNeighbours++;
			}
	//	}
	}

	if(numNeighbours != 0) {
		totalVel = totalVel / numNeighbours;
		return ( totalVel - *b->getDir() ) / ALIGNMENT_COEFF;
	}

	return Vector<float>(0.0, 0.0, 0.0);
}
