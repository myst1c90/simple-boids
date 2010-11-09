/*
	quatdemo.c
	Copyright (c) 2001 Sergio Biasi <sbiasi@sbiasi.com>
	Distribution and use of this is completely free
*/

#include <stdio.h>
#include "quat.h"

void PrintQuat(quat_t q) {
	printf("(%01.2f %01.2f %01.2f %01.2f)", q.s, q.vx, q.vy, q.vz);
}

void PrintRot(quat_rot_t rot) {
	printf("(%01.2f %01.2f %01.2f %01.2f)", rot.theta, rot.nx, rot.ny, rot.nz);
}

void PrintPos(quat_pos_t r) {
	printf("(%01.2f %01.2f %01.2f)", r.x, r.y, r.z);
}

int main(void) {
	quat_rot_t rot1;
	quat_rot_t rot2;
	quat_t q1;
	quat_t q2;
	quat_t q3;
	quat_pos_t r1;
	quat_pos_t r2;

	rot1.theta = 90;
	rot1.nx = 0;
	rot1.ny = 1;
	rot1.nz = 0;
	printf("rot1 = ");
	PrintRot(rot1);
	printf("\n");

	rot2.theta = 90;
	rot2.nx = 1;
	rot2.ny = 0;
	rot2.nz = 0;
	printf("rot2 = ");
	PrintRot(rot2);
	printf("\n");

	printf("\n");

	q1 = quatFromRotation(rot1);
	printf("q1 = ");
	PrintQuat(q1);
	printf("\n");

	printf("rot(q1) = ");
	PrintRot(quatToRotation(q1));
	printf("\n");

	q2 = quatFromRotation(rot2);
	printf("q2 = ");
	PrintQuat(q2);
	printf("\n");

	printf("rot(q2) = ");
	PrintRot(quatToRotation(q2));
	printf("\n");

	q3 = quatMult(q2, q1);
	printf("q3 = q2*q1 = ");
	PrintQuat(q3);
	printf("\n");

	printf("rot(q3) = ");
	PrintRot(quatToRotation(q3));
	printf("\n");

	printf("\n");

	r1.x = 10;
	r1.y = -5;
	r1.z = 0;
	printf("r1 = ");
	PrintPos(r1);
	printf("\n");

	r2 = quatRotate(r1, rot1);
	printf("rot(r1,q1) = ");
	PrintPos(r2);
	printf("\n");

	r2 = quatRotate(r2, rot2);
	printf("rot(rot(r1,q1),q2) = ");
	PrintPos(r2);
	printf("\n");

	r2 = quatRotate(r1, quatToRotation(q3));
	printf("rot(r1,q3) = ");
	PrintPos(r2);
	printf("\n");

	return 1;
}
