/*
 quat.c
 Copyright (c) 2001 Sergio Biasi <sbiasi@sbiasi.com>
 Distribution and use of this is completely free
 */

#include <math.h>
#include "quat.h"

const double halfpi = 1.57079632679489661923132169164;
const double epsilon = 0.000001;

/* Sum of two quaternions */
quat_t quatAdd(quat_t q1, quat_t q2) {
	quat_t qr;

	qr.s = q1.s + q2.s;
	qr.vx = q1.vx + q2.vx;
	qr.vy = q1.vy + q2.vy;
	qr.vz = q1.vz + q2.vz;

	return qr;
}

/* Difference of two quaternions */
quat_t quatSub(quat_t q1, quat_t q2) {
	quat_t qr;

	qr.s = q1.s - q2.s;
	qr.vx = q1.vx - q2.vx;
	qr.vy = q1.vy - q2.vy;
	qr.vz = q1.vz - q2.vz;

	return qr;
}

/* Product of a quaternion and a scalar */
quat_t quatScale(double s, quat_t q1) {
	quat_t qr;

	qr.s = s * q1.s;
	qr.vx = s * q1.vx;
	qr.vy = s * q1.vy;
	qr.vz = s * q1.vz;

	return qr;
}

/* Product of two quaternions */
quat_t quatMult(quat_t q1, quat_t q2) {
	quat_t qr;

	qr.s = q1.s * q2.s - q1.vx * q2.vx - q1.vy * q2.vy - q1.vz * q2.vz;
	qr.vx = q1.s * q2.vx + q2.s * q1.vx + q1.vy * q2.vz - q1.vz * q2.vy;
	qr.vy = q1.s * q2.vy + q2.s * q1.vy + q1.vz * q2.vx - q1.vx * q2.vz;
	qr.vz = q1.s * q2.vz + q2.s * q1.vz + q1.vx * q2.vy - q1.vy * q2.vx;

	return qr;
}

/* Conjugate of a quaternion */
quat_t quatConj(quat_t q) {
	quat_t qr;

	qr.s = q.s;
	qr.vx = -q.vx;
	qr.vy = -q.vy;
	qr.vz = -q.vz;

	return qr;
}

/* Norm of a quaternion */
double quatNorm(quat_t q) {
	return sqrt(q.s * q.s + q.vx * q.vx + q.vy * q.vy + q.vz * q.vz);
}

/* Normalize a quaternion */
/* (or return the original quaternion if its norm is zero) */
quat_t quatNormalize(quat_t q) {
	double norm;
	if ((norm = quatNorm(q)) == 0.0) {
		return q;
	}
	return quatScale(1.0 / norm, q);
}

/* Multiplicative inverse of a quaternion */
/* (or return the original quaternion if its norm is zero) */
quat_t quatInv(quat_t q) {
	double norm;
	if ((norm = quatNorm(q)) == 0.0) {
		return q;
	}
	return quatScale(1.0 / norm, quatConj(q));
}

/* Linear interpolation of two quaternions */
quat_t quatLinearInterpol(quat_t q1, quat_t q2, double t) {
	return quatAdd(quatScale((1.0 - t), q1), quatScale(t, q2));
}

/* Dot (scalar) product of two quaternions */
double quatDot(quat_t q1, quat_t q2) {
	return sqrt(q1.s * q2.s + q1.vx * q2.vx + q1.vy * q2.vy + q1.vz * q2.vz);
}

/* Angular interpolation of two quaternions */
quat_t quatAngularInterpol(quat_t q1, quat_t q2, double u) {
	double cosomega;
	double sinomega;
	double omega;
	double s1, s2;

	if (quatNorm(quatSub(q1, q2)) > quatNorm(quatAdd(q1, q2))) {
		q2 = quatScale(-1, q2);
	}

	cosomega = quatDot(q1, q2);

	if ((1.0 - cosomega) < epsilon) {
		return quatLinearInterpol(q1, q2, u);
	}

	if ((1.0 + cosomega) < epsilon) {
		quat_t q2a;

		q2a.s = -q2.vx;
		q2a.vx = q2.s;
		q2a.vy = -q2.vz;
		q2a.vz = q2.vy;

		s1 = sin((1.0 - u) * halfpi);
		s2 = sin(u * halfpi);

		return quatAdd(quatScale(s1, q1), quatScale(s2, q2a));
	}
	omega = acos(cosomega);
	sinomega = sin(omega);

	s1 = sin((1.0 - u) * omega) / sinomega;
	s2 = sin(u * omega) / sinomega;

	return quatAdd(quatScale(s1, q1), quatScale(s2, q2));
}

/* Recover a (theta,n) rotation from a quaternion */
/*
 theta is the angle of counter-clockwise rotation in degrees */
/*
 n is a vector for the axis of rotation */
quat_rot_t quatToRotation(quat_t q) {
	quat_rot_t rr;

	rr.theta = (acos(q.s) * 180) / halfpi;
	rr.nx = q.vx;
	rr.ny = q.vy;
	rr.nz = q.vz;

	return rr;
}

/* Encode a (theta,n) rotation in a unit quaternion */
/*
 theta is the angle of counter-clockwise rotation in degrees */
/*
 n is a vector for the axis of rotation */
/* (return a quaternion for a null rotation if the vector n is too small) */
quat_t quatFromRotation(quat_rot_t r) {
	quat_t qr;
	double halftheta;
	double sinhalftheta;
	double axisnorm;

	if( (axisnorm = sqrt(r.nx*r.nx + r.ny*r.ny + r.nz*r.nz)) < epsilon) {
		qr.s = 1.0;
		qr.vx = 0.0;
		qr.vy = 0.0;
		qr.vz = 0.0;

		return qr;
	}

	halftheta = (r.theta*halfpi)/180;
	sinhalftheta = sin(halftheta);
	qr.s = cos(halftheta);
	qr.vx = sinhalftheta * (r.nx/axisnorm);
	qr.vy = sinhalftheta * (r.ny/axisnorm);
	qr.vz = sinhalftheta * (r.nz/axisnorm);

	return qr;
}

/* Recover a position from a quaternion */
quat_pos_t quatToPosition(quat_t q) {
	quat_pos_t pr;

	pr.x = q.vx;
	pr.y = q.vy;
	pr.z = q.vz;

	return pr;
}

/* Encode a position in a quaternion */
quat_t quatFromPosition(quat_pos_t p) {
	quat_t qr;

	qr.s = 0.0;
	qr.vx = p.x;
	qr.vy = p.y;
	qr.vz = p.z;

	return qr;
}

/* Compose two rotations using quaternions */
quat_rot_t quatCompose(quat_rot_t r1, quat_rot_t r2) {
	return quatToRotation(quatMult(quatFromRotation(r2), quatFromRotation(r1)));
}

/* Rotate a given position using a given rotation */
quat_pos_t quatRotate(quat_pos_t p, quat_rot_t r) {
	return quatToPosition(quatMult(quatFromRotation(r), quatMult(
			quatFromPosition(p), quatConj(quatFromRotation(r)))));
}

