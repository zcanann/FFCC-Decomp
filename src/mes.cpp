#include "ffcc/mes.h"
#include <string.h>

/*
 * --INFO--
 * Address: 8009b358
 * Size: 92b
 */
CMes::CMes()
{
	mText = 0;
	mCounter = 0;
	*(int*)((char*)this + 0x3c10) = 0;
	*(int*)((char*)this + 0x3c0c) = 0;
	*(int*)((char*)this + 0x3d34) = 0;
	*(int*)((char*)this + 0x3d38) = 1;
	memset((char*)this + 0x3cc0, 0, 0x50);
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMes::~CMes()
{
	// Destructor - no dynamic allocation to clean up in basic implementation
}

/*
 * --INFO--
 * Address: 8009b168
 * Size: 436b
 */
void CMes::Set(char* text, int param)
{
	*(int*)((char*)this + 4) = (int)text;
	*(int*)((char*)this + 0x3c74) = 0;
	*(float*)((char*)this + 0x3ca8) = 0.0f;
	*(float*)((char*)this + 0x3ca4) = 0.0f;
	*(int*)((char*)this + 8) = 0;
	*(int*)((char*)this + 0x3c10) = 0;
	*(int*)((char*)this + 0x3c0c) = 0;
	*(int*)((char*)this + 0x3d10) = 0;
	*(int*)((char*)this + 0x3d30) = param;
	*(float*)((char*)this + 0x3d3c) = 0.0f;
	*(int*)((char*)this + 0x3d40) = 0;
	*(float*)((char*)this + 0x3d44) = 1.0f;
	*(float*)((char*)this + 0x3d48) = 1.0f;
	*(int*)((char*)this + 0x3d4c) = 1;
	
	if (text != 0)
	{
		// Copy data and process text
		memcpy((char*)this + 0x3cc0, (char*)this + 0x3cc0, 0x50);
		
		while (*(int*)((char*)this + 0x3c74) == 0)
		{
			*(int*)((char*)this + 8) = 0;
			*(int*)((char*)this + 0x3c10) = 0;
			*(int*)((char*)this + 0x3c0c) = 0;
			*(float*)((char*)this + 0x3c88) = 0.0f;
			*(float*)((char*)this + 0x3c84) = 0.0f;
			*(float*)((char*)this + 0x3c90) = 0.0f;
			*(float*)((char*)this + 0x3c8c) = 0.0f;
			
			// Call addString - simplified
			break; // Avoid infinite loop for now
		}
		
		// Final setup
		*(int*)((char*)this + 4) = (int)text;
		*(int*)((char*)this + 0x3c74) = 0;
		*(int*)((char*)this + 0x3cb0) = 0;
		*(int*)((char*)this + 0x3cb4) = 3;
		*(int*)((char*)this + 0x3cb8) = 0;
		*(int*)((char*)this + 0x3d10) = 0;
		*(int*)((char*)this + 0x3d2c) = 0;
		*(int*)((char*)this + 0x3d28) = 7;
		*(float*)((char*)this + 0x3d3c) = 0.0f;
		*(int*)((char*)this + 0x3d40) = 0;
		*(float*)((char*)this + 0x3d44) = 1.0f;
		*(float*)((char*)this + 0x3d48) = 1.0f;
		*(int*)((char*)this + 0x3d4c) = 1;
	}
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::Next()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::getFont(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::addString(char **, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::GET_2(char **)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::GET_1(char **)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::GetWait()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::Calc()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::Draw()
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::SetPosition(float x, float y)
{
	// Store position in data array (using offsets that might match original)
	float* xPos = (float*)&mData[0x0C];
	float* yPos = (float*)&mData[0x10];
	*xPos = x;
	*yPos = y;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::useFlag(int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::addFlag(CMes::CFlag&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::CFlag::operator= (const CMes::CFlag&)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::MakeAgbString(char*, char*, int, int)
{
	// TODO
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void CMes::drawTagString(CFont*, char*, int, int, int)
{
	// TODO
}
