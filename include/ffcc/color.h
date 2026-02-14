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

	union {
		GXColor color;
		u32 raw;
	};
};

class CColor3
{
public:
	CColor3();
	CColor3(CColor3& other);
	CColor3(_GXColor& other);

	union {
		GXColor color;
		u32 raw;
	};
};

#endif // _FFCC_COLOR_H_
