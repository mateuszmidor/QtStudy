/*
	Data:
		2006, wrzesieñ

	Unit:
		uMS3D_mathlib

	Opis:
		Modó³ pomocniczy do klasy CMS3DMesh,
		zawiera zestaw funkcji do dzia³ania na macierzach i kwanternionach.
	Autor:
		Mateusz Midor

	MailTo:
		3dmaniac@epf.pl
*/

#include "uMS3D_mathlib.h"

//------------------------------------------------------------------------------
void AngleMatrix(const TMS3DVec3 angles, float (*matrix)[4])
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;
	
	angle = angles[2] * (Q_PI*2 / 360);
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[1] * (Q_PI*2 / 360);
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[0] * (Q_PI*2 / 360);
	sr = sin(angle);
	cr = cos(angle);

	// matrix = (Z * Y) * X
	matrix[0][0] = cp*cy;
	matrix[1][0] = cp*sy;
	matrix[2][0] = -sp;
	matrix[0][1] = sr*sp*cy+cr*-sy;
	matrix[1][1] = sr*sp*sy+cr*cy;
	matrix[2][1] = sr*cp;
	matrix[0][2] = (cr*sp*cy+-sr*-sy);
	matrix[1][2] = (cr*sp*sy+-sr*cy);
	matrix[2][2] = cr*cp;
	matrix[0][3] = 0.0;
	matrix[1][3] = 0.0;
	matrix[2][3] = 0.0;
}

//------------------------------------------------------------------------------
void R_ConcatTransforms(const float in1[3][4], const float in2[3][4], float (*out)[4])
{
	out[0][0] = in1[0][0] * in2[0][0] + in1[0][1] * in2[1][0] +
				in1[0][2] * in2[2][0];
	out[0][1] = in1[0][0] * in2[0][1] + in1[0][1] * in2[1][1] +
				in1[0][2] * in2[2][1];
	out[0][2] = in1[0][0] * in2[0][2] + in1[0][1] * in2[1][2] +
				in1[0][2] * in2[2][2];
	out[0][3] = in1[0][0] * in2[0][3] + in1[0][1] * in2[1][3] +
				in1[0][2] * in2[2][3] + in1[0][3];
	out[1][0] = in1[1][0] * in2[0][0] + in1[1][1] * in2[1][0] +
				in1[1][2] * in2[2][0];
	out[1][1] = in1[1][0] * in2[0][1] + in1[1][1] * in2[1][1] +
				in1[1][2] * in2[2][1];
	out[1][2] = in1[1][0] * in2[0][2] + in1[1][1] * in2[1][2] +
				in1[1][2] * in2[2][2];
	out[1][3] = in1[1][0] * in2[0][3] + in1[1][1] * in2[1][3] +
				in1[1][2] * in2[2][3] + in1[1][3];
	out[2][0] = in1[2][0] * in2[0][0] + in1[2][1] * in2[1][0] +
				in1[2][2] * in2[2][0];
	out[2][1] = in1[2][0] * in2[0][1] + in1[2][1] * in2[1][1] +
				in1[2][2] * in2[2][1];
	out[2][2] = in1[2][0] * in2[0][2] + in1[2][1] * in2[1][2] +
				in1[2][2] * in2[2][2];
	out[2][3] = in1[2][0] * in2[0][3] + in1[2][1] * in2[1][3] +
				in1[2][2] * in2[2][3] + in1[2][3];
}

//------------------------------------------------------------------------------
void VectorRotate(const TMS3DVec3 in1, const float in2[3][4], TMS3DVec3 &out)
{
	out[0] = in1[0]*in2[0][0] + in1[1]*in2[0][1] + in1[2]*in2[0][2];
	out[1] = in1[0]*in2[1][0] + in1[1]*in2[1][1] + in1[2]*in2[1][2];
	out[2] = in1[0]*in2[2][0] + in1[1]*in2[2][1] + in1[2]*in2[2][2];
}

//------------------------------------------------------------------------------
// rotate by the inverse of the matrix
void VectorIRotate (const TMS3DVec3 in1, const float in2[3][4], TMS3DVec3 &out)
{
	out[0] = in1[0]*in2[0][0] + in1[1]*in2[1][0] + in1[2]*in2[2][0];
	out[1] = in1[0]*in2[0][1] + in1[1]*in2[1][1] + in1[2]*in2[2][1];
	out[2] = in1[0]*in2[0][2] + in1[1]*in2[1][2] + in1[2]*in2[2][2];
}

//------------------------------------------------------------------------------
void AngleQuaternion(const TMS3DVec3 angles, TMS3DVec4 &quaternion )
{
	float		angle;
	float		sr, sp, sy, cr, cp, cy;

	// FIXME: rescale the inputs to 1/2 angle
	angle = angles[2] * 0.5;
	sy = sin(angle);
	cy = cos(angle);
	angle = angles[1] * 0.5;
	sp = sin(angle);
	cp = cos(angle);
	angle = angles[0] * 0.5;
	sr = sin(angle);
	cr = cos(angle);

	quaternion[0] = sr*cp*cy-cr*sp*sy; // X
	quaternion[1] = cr*sp*cy+sr*cp*sy; // Y
	quaternion[2] = cr*cp*sy-sr*sp*cy; // Z
	quaternion[3] = cr*cp*cy+sr*sp*sy; // W
}

//------------------------------------------------------------------------------
void QuaternionMatrix(const TMS3DVec4 quaternion, float (*matrix)[4] )
{

	matrix[0][0] = 1.0 - 2.0 * quaternion[1] * quaternion[1] - 2.0 * quaternion[2] * quaternion[2];
	matrix[1][0] = 2.0 * quaternion[0] * quaternion[1] + 2.0 * quaternion[3] * quaternion[2];
	matrix[2][0] = 2.0 * quaternion[0] * quaternion[2] - 2.0 * quaternion[3] * quaternion[1];

	matrix[0][1] = 2.0 * quaternion[0] * quaternion[1] - 2.0 * quaternion[3] * quaternion[2];
	matrix[1][1] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[2] * quaternion[2];
	matrix[2][1] = 2.0 * quaternion[1] * quaternion[2] + 2.0 * quaternion[3] * quaternion[0];

	matrix[0][2] = 2.0 * quaternion[0] * quaternion[2] + 2.0 * quaternion[3] * quaternion[1];
	matrix[1][2] = 2.0 * quaternion[1] * quaternion[2] - 2.0 * quaternion[3] * quaternion[0];
	matrix[2][2] = 1.0 - 2.0 * quaternion[0] * quaternion[0] - 2.0 * quaternion[1] * quaternion[1];
}

//------------------------------------------------------------------------------
void QuaternionSlerp(const TMS3DVec4 p, TMS3DVec4 q, const float t, TMS3DVec4 &qt )
{
	int i;
	float omega, cosom, sinom, sclp, sclq;

	// decide if one of the quaternions is backwards
	float a = 0;
	float b = 0;
	for (i = 0; i < 4; i++) {
		a += (p[i] - q[i]) * (p[i] - q[i]);
		b += (p[i] + q[i]) * (p[i] + q[i]);
	}
	if (a > b) {
		for (i = 0; i < 4; i++) {
			q[i] = -q[i];
		}
	}

	cosom = p[0] * q[0] + p[1] * q[1] + p[2] * q[2] + p[3] * q[3];

	if ((1.0 + cosom) > 0.00000001) {
		if ((1.0 - cosom) > 0.00000001) {
			omega = acos( cosom );
			sinom = sin( omega );
			sclp = sin( (1.0 - t)*omega) / sinom;
			sclq = sin( t*omega ) / sinom;
		}
		else {
			sclp = 1.0 - t;
			sclq = t;
		}
		for (i = 0; i < 4; i++) {
			qt[i] = sclp * p[i] + sclq * q[i];
		}
	}
	else {
		qt[0] = -p[1];
		qt[1] = p[0];
		qt[2] = -p[3];
		qt[3] = p[2];
		sclp = sin( (1.0 - t) * 0.5 * Q_PI);
		sclq = sin( t * 0.5 * Q_PI);
		for (i = 0; i < 3; i++) {
			qt[i] = sclp * p[i] + sclq * qt[i];
		}
	}
}