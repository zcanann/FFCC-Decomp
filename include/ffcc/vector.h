#ifndef _FFCC_VECTOR_H_
#define _FFCC_VECTOR_H_

#include <dolphin/mtx.h>

class CVector
{
public:
	CVector();
	CVector(float, float, float);
	CVector(const Vec&);
	CVector operator+(const CVector&) const;
	CVector operator-(const CVector&) const;
	operator Vec&() { return *reinterpret_cast<Vec*>(this); }
	operator Vec*() { return reinterpret_cast<Vec*>(this); }
	void operator=(const CVector&);

	void Identity();
	void Normalize();
	float GetRotateY();
	
	float x;
	float y;
	float z;
};

#endif // _FFCC_VECTOR_H_
