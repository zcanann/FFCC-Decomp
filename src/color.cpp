#include "ffcc/color.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor::CColor()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor::CColor(unsigned char r, unsigned char g, unsigned char b, unsigned char a)
{
	this->color.r = r;
	this->color.g = g;
	this->color.b = b;
	this->color.a = a;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor::CColor(CColor& other)
{
	this->raw = other.raw;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor::CColor(_GXColor& other)
{
	this->raw = *(u32*)&other;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor3::CColor3()
{
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor3::CColor3(CColor3& other)
{
	this->raw = other.raw;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor3::CColor3(_GXColor& other)
{
	this->raw = *(u32*)&other;
}
