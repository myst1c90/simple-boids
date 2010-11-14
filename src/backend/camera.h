/*
 * Camera.h
 *
 *  Created on: Nov 14, 2010
 *      Author: lucmir
 */

#include "vector.h"

#ifndef CAMERA_H_
#define CAMERA_H_


class Camera {

	Vector<float> *eye;
	Vector<float> *center;
	Vector<float> *up;


	public:

		Camera(Vector<float> *initEye, Vector<float> *initCenter, Vector<float> *initUp);
		Camera(float eyeX, float eyeY, float eyeZ, float centerX, float centerY,
			float centerZ, float upX, float upY, float upZ);
		virtual ~Camera();

		void set(float eyeX, float eyeY, float eyeZ, float centerX, float centerY,
			float centerZ, float upX, float upY, float upZ);
		void setEye(float x, float y, float z);
		void setCenter(float x, float y, float z);
		void setUp(float x, float y, float z);

		float getEyeX();
		float getEyeY();
		float getEyeZ();

		float getCenterX();
		float getCenterY();
		float getCenterZ();

		float getUpX();
		float getUpY();
		float getUpZ();

};

#endif /* CAMERA_H_ */
