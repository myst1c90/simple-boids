/*
 * Camera.cpp
 *
 *  Created on: Nov 14, 2010
 *      Author: lucmir
 */

#include "camera.h"

Camera::Camera(Vector<float> *initEye, Vector<float> *initCenter, Vector<float> *initUp) {
	eye = initEye;
	center = initCenter;
	up = initUp;
}

Camera::Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY,
	float centerZ, float upX, float upY, float upZ) {
	eye = new Vector<float>(eyeX, eyeY, eyeZ);
	center = new Vector<float>(centerX, centerY, centerZ);
	up = new Vector<float>(upX, upY, upZ);
}

Camera::~Camera() {
}

void Camera::set(float eyeX, float eyeY, float eyeZ, float centerX, float centerY,
	float centerZ, float upX, float upY, float upZ) {
	eye->set(eyeX, eyeY, eyeZ);
	center->set(centerX, centerY, centerZ);
	up->set(upX, upY, upZ);
}

void Camera::setEye(float x, float y, float z) {
	eye->set(x, y, z);
}

void Camera::setCenter(float x, float y, float z) {
	center->set(x, y, z);
}

void Camera::setUp(float x, float y, float z) {
	up->set(x, y, z);
}

float Camera::getEyeX() {
	return eye->getX();
}

float Camera::getEyeY() {
	return eye->getY();
}

float Camera::getEyeZ() {
	return eye->getZ();
}

float Camera::getCenterX() {
	return center->getX();
}

float Camera::getCenterY() {
	return center->getY();
}

float Camera::getCenterZ() {
	return center->getZ();
}

float Camera::getUpX() {
	return up->getX();
}

float Camera::getUpY() {
	return up->getY();
}

float Camera::getUpZ() {
	return up->getZ();
}

