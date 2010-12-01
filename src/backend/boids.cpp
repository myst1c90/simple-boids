/*
 * Boids.cpp
 *
 *  Created on: Nov 8, 2010
 *      Author: lucmir
 */

#include "boids.h"

Boids::Boids() {
	boids = new std::vector<Bird *>();
	centerPos = new Vector<float>(0.0,0.0,0.0);
	centerDir = new Vector<float>(0.0,0.0,0.0);
	cohesionCoeff = 0.5;
	separationCoeff = 0.3;
	aligmentCoeff = 0.1;
	obstacleAvoidCoeff = 0.15;
	minDistance = 0.3;
}

Boids::~Boids() {
	boids->clear();
	delete(boids);
}

bool Boids::addBoid(Bird *bird) {
	for(unsigned int i=0; i<boids->size(); i++) {
		Bird *b_i = (*boids)[i];
		Vector<float> distVec = *bird->getPos() - *b_i->getPos();
		float dist = distVec.magnitude();
		if(dist < MIN_SPACE) {
			return false;
		}
	}
	boids->push_back(bird);
	return true;
}

void Boids::removeLastBoid() {
	boids->pop_back();
}

std::vector<Bird *> *Boids::getBoids() {
	return boids;
}

/*
 * Boids algorithms
 */
void Boids::updateBoidsPosition(Entity *obstacle) {
	int numBoids = boids->size();

	// compute new position for all the boids
	int numNeighbors = updateCenter();
	if(numNeighbors > 1) {
		Vector<float> newPosList1[numBoids];
		Vector<float> newPosList2[numBoids];
		Vector<float> newPosList3[numBoids];

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

			*b->getDir() += (*newPos1 + *newPos2 + *newPos3 + avoidObstacle(i, obstacle)) / BOIDS_VEL_COEFF;
			*b->getPos() += *b->getDir();
			 b->setVel( (b->getDir())->magnitude() );
		}
	}
}

int Boids::updateCenter() {
	int numNeighbours = 0;
	int numBoids = boids->size();
	centerPos->set(0.0,0.0,0.0);
	centerDir->set(0.0,0.0,0.0);

	for(int i=0; i<numBoids; i++) {
			Bird *b_i = (*boids)[i];
			*centerPos = *centerPos + (*b_i->getPos());
			*centerDir = *centerDir - (*b_i->getDir());
			numNeighbours++;
	}

	if(numNeighbours != 0) {
		*centerPos = *centerPos / numNeighbours;
		*centerDir = *centerDir / numNeighbours;
	}

	return numNeighbours;
}


// rule 1: Cohesion - boids try to fly towards the centre of mass of neighbouring boids.
Vector<float> Boids::rule1(int boidNum) {
	Bird *b = (*boids)[boidNum];
	return ( ( *centerPos - *b->getPos() ) / cohesionCoeff );
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

//			if(dist < MIN_DISTANCE)	{
				Vector<float> unitVect = distVec / dist;
				disp = disp + unitVect * (separationCoeff-dist);
//			}
		}
	}

	return disp;
}

// rule 3: alignment - the boids try to match their velocity with their neighbours.
Vector<float> Boids::rule3(int boidNum) {
	Bird *b = (*boids)[boidNum];
	return ( *centerDir - *b->getDir() ) / aligmentCoeff;
}

Vector<float> Boids::avoidObstacle(int boidNum, Entity *obstacle) {

	Vector<float> newVec(0.0,0.0,0.0);
	Bird *b = (*boids)[boidNum];

	Vector<float> *obstaclePos = obstacle->getPos();
	float obstacleH = obstacle->getVol()->getY();
	float obstacleR = obstacle->getVol()->getX();
	float h = - b->getPos()->getY();
	float r = ( obstacleR * (obstacleH - h) ) / obstacleH;

	if( h > (obstacleH + MIN_SPACE) ) {
		return newVec;
	}

	Vector<float> pos(obstaclePos->getX(), -h, obstaclePos->getZ());
	Vector<float> distVec = *b->getPos() - pos;
	distVec.setY(0.0);
	float dist = distVec.magnitude();

	if(dist < (r + MIN_SPACE) ) {
		newVec = newVec - ( pos - *b->getPos() ) / obstacleAvoidCoeff;
	}

	return newVec;
}


Vector<float> *Boids::getCenterPos() {
	return centerPos;
}

Vector<float> *Boids::getCenterDir() {
	return centerDir;
}

void Boids::setCohesionCoeff(float coeff) {
	cohesionCoeff = coeff;
}

void Boids::setSeparationCoeff(float coeff) {
	separationCoeff = coeff;
	minDistance = separationCoeff;
}

void Boids::setAligmentCoeff(float coeff) {
	aligmentCoeff = coeff;
}

void Boids::setObstacleAvoidCoeff(float coeff) {
	obstacleAvoidCoeff = coeff;
}

