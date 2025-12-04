#ifndef _FFCC_COLOR_H_
#define _FFCC_COLOR_H_

#include <dolphin/gx.h>

class CColor
{
public:
	CColor();
	CColor(unsigned char, unsigned char, unsigned char, unsigned char);
	CColor(CColor &);
	CColor(_GXColor &);
};

class CColor3
{
public:
	CColor3();
	CColor3(CColor3 &);
	CColor3(_GXColor &);
};

#endif // _FFCC_COLOR_H_
