#ifndef _FFCC_VECTOR_H_
#define _FFCC_VECTOR_H_

#include "dolphin/mtx/GeoTypes.h"

class CVector
{
	CVector();
	CVector(float, float, float);
	CVector(const Vec &);
	void Identity();
	void Normalize();
	float GetRotateY();
	
	float x;
	float y;
	float z;
};

#endif
