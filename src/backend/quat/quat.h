/*
	quat.h
	Copyright(c) 2001 Sergio Biasi <sbiasi@sbiasi.com>
	Distribution and use of this is completely free
*/

#ifndef _QUAT_H_INCLUDED_
#define _QUAT_H_INCLUDED_

typedef struct {
	double s;
	double vx;
	double vy;
	double vz;
} quat_t;

typedef struct {
	double theta;
	double nx;
	double ny;
	double nz;
} quat_rot_t;

typedef struct
{
	double x;
	double y;
	double z;
} quat_pos_t;


quat_t quatAdd(quat_t q1, quat_t q2);
quat_t quatSub(quat_t q1, quat_t q2);
quat_t quatScale(double s, quat_t q1);
quat_t quatMult(quat_t q1, quat_t q2);
quat_t quatConj(quat_t q);
double quatNorm(quat_t q);
quat_t quatNormalize(quat_t q);
quat_t quatInv(quat_t q);
quat_t quatLinearInterpol(quat_t q1, quat_t q2, double t);
double quatDot(quat_t q1, quat_t q2);
quat_t quatAngularInterpol(quat_t q1, quat_t q2, double u);

quat_rot_t quatToRotation(quat_t q);
quat_t quatFromRotation(quat_rot_t r);

quat_pos_t quatToPosition(quat_t q);
quat_t quatFromPosition(quat_pos_t p);

quat_rot_t quatCompose(quat_rot_t r1, quat_rot_t r2);
quat_pos_t quatRotate(quat_pos_t p, quat_rot_t r);


#endif /* _QUAT_H_INCLUDED_ */

