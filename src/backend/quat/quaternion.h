/*
 * quaternion.h
 *
 *  Created on: Nov 9, 2010
 *      Author: lucmir
 */

#ifndef _QUATERNION_H_INCLUDED_
#define _QUATERNION_H_INCLUDED_


#include <math.h>

#ifndef 	PI
#define		PI		3.14159265358979323846
#endif


class Quaternion {

	float m_w;
	float m_z;
	float m_y;
	float m_x;

	public:

		Quaternion();
		virtual ~Quaternion();

		Quaternion operator *(Quaternion q);
		void createMatrix(float *pMatrix);
		void createFromAxisAngle(float x, float y, float z, float degrees);
};




#endif /* QUARTENION_H_ */
