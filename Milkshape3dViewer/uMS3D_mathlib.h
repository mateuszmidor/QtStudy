
#ifndef __MS3D_MATHLIB_H__
#define __MS3D_MATHLIB_H__

#include <math.h>


#define	Q_PI	3.14159265358979323846

#ifndef CopyVec3
#define CopyVec3(vDst,vSrc)	(vDst[0] = vSrc[0]); (vDst[1] = vSrc[1]); (vDst[2] = vSrc[2]);
#endif

typedef float	TMS3DFloat;
typedef TMS3DFloat	TMS3DVec3[3];
typedef TMS3DFloat	TMS3DVec4[4];
typedef TMS3DFloat	TMatrix3x4[3][4];

void AngleMatrix(const TMS3DVec3 angles, float matrix[3][4]);
void R_ConcatTransforms(const float in1[3][4], const float in2[3][4], float out[3][4]);
void VectorIRotate(const TMS3DVec3 in1, const float in2[3][4], TMS3DVec3 &out);
void VectorRotate(const TMS3DVec3 in1, const float in2[3][4], TMS3DVec3 &out);
void AngleQuaternion(const TMS3DVec3 angles, TMS3DVec4 &quaternion);
void QuaternionMatrix(const TMS3DVec4 quaternion, float (*matrix)[4]);
void QuaternionSlerp(const TMS3DVec4 p, TMS3DVec4 q, const float t, TMS3DVec4 &qt);


#endif //__MS3D_MATHLIB_H__