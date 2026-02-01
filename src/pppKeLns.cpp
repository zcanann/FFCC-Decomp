#include "ffcc/pppKeLns.h"
#include "ffcc/KeLns.h"

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsLpCon(void** param)
{
	// Access nested pointer structure: param->field[0xc]->field[0x0] + 0x80
	void** nestedPtr = (void**)param[3]; // offset 0xc = 3 * sizeof(ptr)
	char* basePtr = (char*)nestedPtr[0];
	_KeLnsLp* lensPtr = (_KeLnsLp*)(basePtr + 0x80);
	
	// Initialize lens structure
	KeLnsLp_Init(lensPtr);
	
	// Set floating-point values to 0.0
	*(float*)(basePtr + 0x80 + 0x8c) = 0.0f;
	*(float*)(basePtr + 0x80 + 0x98) = 0.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsLpCon2(void** param)
{
	// Similar access pattern to pppKeLnsLpCon but no KeLnsLp_Init call
	void** nestedPtr = (void**)param[3]; // offset 0xc = 3 * sizeof(ptr)
	char* basePtr = (char*)nestedPtr[0];
	
	// Set floating-point values to 0.0
	*(float*)(basePtr + 0x80 + 0x8c) = 0.0f;
	*(float*)(basePtr + 0x80 + 0x98) = 0.0f;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsLpDraw(void)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsCon(void)
{
	return;
}

/*
 * --INFO--
 * Address:	TODO
 * Size:	TODO
 */
void pppKeLnsFlsDraw(void)
{
	return;
}
