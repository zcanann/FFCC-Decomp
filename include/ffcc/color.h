#ifndef _FFCC_COLOR_H_
#define _FFCC_COLOR_H_

#include <dolphin/gx.h>

class CColor
{
public:
	CColor();
	CColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a);
	CColor(CColor& other);
	CColor(_GXColor& other);
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: UNUSED
	 * EN Address: 0x8008A430
	 * EN Size: 36b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	void operator=(const CColor& other)
	{
		color.r = other.color.r;
		color.g = other.color.g;
		color.b = other.color.b;
		color.a = other.color.a;
	}
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: TODO
	 * EN Address: 0x8008A454
	 * EN Size: 276b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	CColor operator*(float scale) const
	{
		CColor out;
		out.color.r = static_cast<unsigned char>(color.r * scale);
		out.color.g = static_cast<unsigned char>(color.g * scale);
		out.color.b = static_cast<unsigned char>(color.b * scale);
		out.color.a = static_cast<unsigned char>(color.a * scale);
		return out;
	}
	/*
	 * --INFO--
	 * PAL Address: UNUSED
	 * PAL Size: TODO
	 * EN Address: 0x8008A654
	 * EN Size: 156b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	CColor operator+(const CColor& other) const
	{
		CColor out;
		out.color.r = color.r + other.color.r;
		out.color.g = color.g + other.color.g;
		out.color.b = color.b + other.color.b;
		out.color.a = color.a + other.color.a;
		return out;
	}
	operator CColor&() { return *this; }
	operator _GXColor();
	/*
	 * --INFO--
	 * PAL Address: 0x800B9224
	 * PAL Size: 4b
	 * EN Address: 0x80044340
	 * EN Size: 4b
	 * JP Address: TODO
	 * JP Size: TODO
	 */
	operator _GXColor*() { return &color; }
	void Identity()
	{
		color.r = 0xFF;
		color.g = 0xFF;
		color.b = 0xFF;
		color.a = 0xFF;
	}
	CColor& Ref() { return *this; }

	GXColor color;
};

class CColor3
{
public:
	CColor3();
	CColor3(unsigned char r, unsigned char g, unsigned char b)
	{
		color.r = r;
		color.g = g;
		color.b = b;
		color.a = 0xFF;
	}
	CColor3(CColor3& other);
	CColor3(_GXColor& other);
	CColor3 operator*(const CColor& other) const
	{
		CColor3 result;
		result.color.r = static_cast<unsigned char>((static_cast<int>(color.r) * other.color.r) / 255);
		result.color.g = static_cast<unsigned char>((static_cast<int>(color.g) * other.color.g) / 255);
		result.color.b = static_cast<unsigned char>((static_cast<int>(color.b) * other.color.b) / 255);
		result.color.a = color.a;
		return result;
	}

	GXColor color;
};

#endif // _FFCC_COLOR_H_
