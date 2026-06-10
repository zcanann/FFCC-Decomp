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
	operator _GXColor();
	operator _GXColor*();
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

	GXColor color;
};

#endif // _FFCC_COLOR_H_
