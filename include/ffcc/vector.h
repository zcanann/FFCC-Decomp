#ifndef _FFCC_VECTOR_H_
#define _FFCC_VECTOR_H_

#include <dolphin/mtx.h>

class CVector
{
public:
	CVector();
	CVector(float, float, float);
	CVector(const Vec&);
	/*
	 * --INFO--
	 * PAL Address: 0x800B9868
	 * PAL Size: 28b
	 * EN Address: TODO
	 * EN Size: TODO
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	CVector(const CVector& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}
	CVector operator+(const CVector&) const;
	/*
	 * --INFO--
	 * PAL Address: 0x800B9884
	 * PAL Size: 112b
	 * EN Address: TODO
	 * EN Size: TODO
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	CVector operator-(const CVector& other) const
	{
		CVector out;
		PSVECSubtract((const Vec*)this, (const Vec*)&other, (Vec*)&out);
		return out;
	}
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
