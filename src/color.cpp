#include "ffcc/color.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor3::CColor3(_GXColor& other)
{
	*(u32*)&this->color = *(u32*)&other;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor3::CColor3(CColor3& other)
{
	*(u32*)&this->color = *(u32*)&other.color;
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
CColor::CColor(_GXColor& other)
{
	*(u32*)&this->color = *(u32*)&other;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CColor::CColor(CColor& other)
{
	*(u32*)&this->color = *(u32*)&other.color;
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
CColor::CColor()
{
}
