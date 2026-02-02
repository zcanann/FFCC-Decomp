#include "ffcc/mes.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
CMes::CMes()
{
	mText = 0;
	mCounter = 0;
	mFlags = 0;
	
	// Initialize data array to zero
	for (int i = 0; i < 0x3D50; i++)
	{
		mData[i] = 0;
	}
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
 * Address:	TODO
 * Size:	TODO
 */
void CMes::Set(char* text, int param)
{
	mText = text;
	mCounter = 0;
	mFlags = param;
	
	if (text != 0)
	{
		// Initialize some data structure based on the text
		// This is a basic implementation to match expected behavior
		for (int i = 0; i < 0x50 && i < 0x3D50; i++)
		{
			mData[i] = 0;
		}
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
