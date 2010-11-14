/*
 * quaternion.cpp
 *
 *  Created on: Nov 9, 2010
 *      Author: lucmir
 */

#include "quaternion.h"


Quaternion::Quaternion() {
	m_x = m_y = m_z = 0.0f;
	m_w = 1.0f;
}

Quaternion::~Quaternion() {

}

void Quaternion::createFromAxisAngle(float x, float y, float z, float degrees) {
	// convert the degrees to radians
	float angle = float((degrees / 180.0f) * PI);

	// calculate the sin( theta / 2) once for optimization
	float result = (float) sin(angle / 2.0f);

	// calculate the w value by cos( theta / 2 )
	m_w = (float) cos(angle / 2.0f);

	// calculate the x, y and z of the quaternion
	m_x = x * result;
	m_y = y * result;
	m_z = z * result;
}

void Quaternion::createMatrix(float *pMatrix) {
	// make sure the matrix has allocated memory to store the rotation data
	if(!pMatrix) {
		return;
	}

	// first row
	pMatrix[ 0] = 1.0f - 2.0f * ( m_y * m_y + m_z * m_z );
	pMatrix[ 1] = 2.0f * (m_x * m_y + m_z * m_w);
	pMatrix[ 2] = 2.0f * (m_x * m_z - m_y * m_w);
	pMatrix[ 3] = 0.0f;

	// second row
	pMatrix[ 4] = 2.0f * ( m_x * m_y - m_z * m_w );
	pMatrix[ 5] = 1.0f - 2.0f * ( m_x * m_x + m_z * m_z );
	pMatrix[ 6] = 2.0f * (m_z * m_y + m_x * m_w );
	pMatrix[ 7] = 0.0f;

	// third row
	pMatrix[ 8] = 2.0f * ( m_x * m_z + m_y * m_w );
	pMatrix[ 9] = 2.0f * ( m_y * m_z - m_x * m_w );
	pMatrix[10] = 1.0f - 2.0f * ( m_x * m_x + m_y * m_y );
	pMatrix[11] = 0.0f;

	// fourth row
	pMatrix[12] = 0;
	pMatrix[13] = 0;
	pMatrix[14] = 0;
	pMatrix[15] = 1.0f;

	// now pMatrix[] is a 4x4 homogeneous matrix
	// that can be applied to an OpenGL Matrix
}

Quaternion Quaternion::operator *(Quaternion q) {
	Quaternion r;

	r.m_w = m_w*q.m_w - m_x*q.m_x - m_y*q.m_y - m_z*q.m_z;
	r.m_x = m_w*q.m_x + m_x*q.m_w + m_y*q.m_z - m_z*q.m_y;
	r.m_y = m_w*q.m_y + m_y*q.m_w + m_z*q.m_x - m_x*q.m_z;
	r.m_z = m_w*q.m_z + m_z*q.m_w + m_x*q.m_y - m_y*q.m_x;

	return(r);
}
