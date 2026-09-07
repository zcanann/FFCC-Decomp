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
	/*
	 * --INFO--
	 * PAL Address: 0x800B97DC
	 * PAL Size: 112b
	 * EN Address: TODO
	 * EN Size: TODO
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	CVector operator+(const CVector& other) const
	{
		CVector out;

		PSVECAdd((const Vec*)this, (const Vec*)&other, (Vec*)&out);
		return out;
	}
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
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: TODO
	 * EN Address: 0x80044694
	 * EN Size: 76b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	CVector operator*(float scale) const
	{
		CVector out;

		PSVECScale((const Vec*)this, (Vec*)&out, scale);
		return out;
	}
	operator Vec&() { return *reinterpret_cast<Vec*>(this); }
	operator Vec*() { return reinterpret_cast<Vec*>(this); }

	/*
	 * --INFO--
	 * PAL Address: 0x800B984C
	 * PAL Size: 28b
	 * EN Address: 0x80083CB8
	 * EN Size: 28b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	void operator=(const CVector& other)
	{
		x = other.x;
		y = other.y;
		z = other.z;
	}

	void Identity();
	void Normalize();
	float GetRotateY();
	
	float x;
	float y;
	float z;
};

#endif // _FFCC_VECTOR_H_
